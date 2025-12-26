# PROJECT REPORT
## Simple Stock Tracker

<br><br><br><br>

**Submitted by:**
[Your Name]
[Your Roll Number]

**Guided by:**
[Guide Name]

<br><br><br><br>

**[Your Institute/College Name]**
[Year]

---

<div style="page-break-after: always;"></div>

# 2. Certificate

This is to certify that **[Your Name]** has successfully completed the project entitled **"Simple Stock Tracker"** under my guidance and supervision in partial fulfillment of the requirements for the course.

<br><br>

**Date:** _________________

**Signature of Guide:** _________________

**Signature of HOD:** _________________

---

<div style="page-break-after: always;"></div>

# 3. Table of Contents

1. [Problem Statement](#4-problem-statement)
2. [Introduction](#5-introduction)
3. [Overview of the project (Block diagram)](#6-overview-of-the-project-block-diagram)
4. [Tools Used](#7-tools-used)
5. [OOPs concept used & its explanation](#8-oops-concept-used--its-explanation)
6. [Implementation/code](#9-implementationcode)
7. [Result /snapshots](#10-result-snapshots)
8. [References](#11-references)

---

<div style="page-break-after: always;"></div>

# 4. Problem Statement

In the fast-paced world of finance, keeping track of stock market prices is essential for investors and traders. However, many existing tools are complex, cluttered, or require paid subscriptions. 

The problem addressed by this project is the need for a **lightweight, user-friendly, and free desktop application** that allows users to:
1.  Track real-time prices of specific stocks they are interested in.
2.  Visualize price trends over time without complex charts.
3.  Manage a personalized watchlist easily.

The solution aims to simplify stock tracking by fetching data directly from a reliable API and presenting it in a clean, intuitive interface with essential features like price history and dark mode for better usability.

# 5. Introduction

The **Simple Stock Tracker** is a Java-based desktop application designed to provide users with up-to-date stock market information. It leverages the **Alpha Vantage API** to fetch real-time global stock quotes and daily historical data.

Key features of the application include:
*   **Real-time Stock Monitoring:** Users can add stock symbols (e.g., AAPL, GOOGL) to a watchlist and see their current price and daily change.
*   **Graphical Analysis:** A 30-day price history graph helps users analyze trends visually.
*   **User Personalization:** The application supports a Dark Mode/Light Mode toggle to suit user preference and lighting conditions.
*   **Responsive UI:** Built with Java Swing, the interface is robust and responsive.

This project demonstrates the integration of a RESTful API with a Java GU application, handling JSON parsing, network requests, and dynamic UI updates.

# 6. Overview of the project (Block diagram)

The project follows a modular architecture separating the User Interface (GUI), Data Model, and Service Layer.

### Block Diagram

```mermaid
graph TD
    User[User] -->|Interacts| GUI[StockTrackerGUI (View)]
    GUI -->|Request Data| Service[StockService (Controller/Service)]
    Service -->|HTTP Request| API[Alpha Vantage API (External)]
    API -->|JSON Response| Service
    Service -->|Returns Objects| Model[Stock Object (Model)]
    Model -->|Updates| GUI
    GUI -->|Display| Graph[StockGraphDialog]
```

*   **StockTrackerGUI:** The main window handling user inputs and displaying the table of stocks.
*   **StockService:** Handles all network communication with Alpha Vantage, parses JSON responses, and returns structured data.
*   **Stock:** A POJO (Plain Old Java Object) representing a single stock's data.
*   **StockGraphDialog:** A separate window for rendering the price history chart.

# 7. Tools Used

*   **Programming Language:** Java (JDK 17+)
*   **IDE:** Visual Studio Code / Eclipse / IntelliJ IDEA
*   **GUI Framework:** Java Swing (javax.swing)
*   **External Libraries:** `org.json` (json-20231013.jar) for parsing API responses.
*   **API:** Alpha Vantage (Free tier for stock market data)
*   **Build Tool:** Simple `javac` command line or IDE build system.

# 8. OOPs concept used & its explanation

Object-Oriented Programming (OOP) principles are the foundation of this application, ensuring code maintainability and scalability.

### 1. Encapsulation
Encapsulation is used to bundle data and methods that operate on that data within a single unit (class) and restricting access to some of the object's components.
*   **Example:** The `Stock` class declares its fields (`symbol`, `price`, etc.) as `private` and provides public `getter` and `setter` methods to access them. This protects the data from unauthorized direct modification.

### 2. Inheritance
Inheritance allows a class to inherit properties and methods from another class.
*   **Example:** `StockTrackerGUI` extends `JFrame`. By doing this, our class automatically gains all the features of a window (title bar, close button, resizing) without rewriting code. `StockGraphDialog` similarly extends `JDialog`.

### 3. Polymorphism
Polymorphism allows objects to be treated as instances of their parent class.
*   **Example:** We use **Method Overriding** in the table renderers. The `DefaultTableCellRenderer` is extended, and the `getTableCellRendererComponent` method is overridden to implement custom logic (like changing text color to green/red based on positive/negative change).
*   **Example:** Event listeners like `ActionListener` use polymorphism where we provide specific implementations for button clicks (Lambda expressions).

### 4. Abstraction
Abstraction involves hiding complex implementation details and showing only the necessary features of an object.
*   **Example:** The `StockService` class abstracts the complexity of making HTTP requests and parsing JSON. The GUI doesn't know *how* the data is fetched; it simply calls `stockService.getStock("AAPL")`.

# 9. Implementation/code

### Stock.java (Model)
```java
package com.example.stocktracker;

public class Stock {
    private String symbol;
    private String name;
    private double price;
    private double change;

    public Stock(String symbol, String name, double price, double change) {
        this.symbol = symbol;
        this.name = name;
        this.price = price;
        this.change = change;
    }

    public String getSymbol() { return symbol; }
    public double getPrice() { return price; }
    // ... getters and setters
}
```

### StockService.java (Fetching Data)
```java
public class StockService {
    private static final String API_KEY = "YOUR_API_KEY";
    private static final String BASE_URL = "https://www.alphavantage.co/query";

    public Stock getStock(String symbol) {
        // Construct URL
        String urlStr = String.format("%s?function=GLOBAL_QUOTE&symbol=%s&apikey=%s", 
                                      BASE_URL, symbol, API_KEY);
        // Fetch JSON
        JSONObject json = fetchJson(urlStr);
        // Parse and return Stock object
        if (json.has("Global Quote")) {
             JSONObject quote = json.getJSONObject("Global Quote");
             double price = Double.parseDouble(quote.getString("05. price"));
             // ...
             return new Stock(symbol, name, price, change);
        }
        return null;
    }
}
```

### StockTrackerGUI.java (Dark Mode Implementation)
```java
private void applyTheme() {
    Color bgColor, fgColor;
    if (isDarkMode) {
        bgColor = new Color(45, 45, 45);
        fgColor = new Color(230, 230, 230);
    } else {
        bgColor = UIManager.getColor("Panel.background");
        fgColor = Color.BLACK;
    }
    getContentPane().setBackground(bgColor);
    // Recursively update components
    SwingUtilities.updateComponentTreeUI(this);
}
```

# 10. Result /snapshots

### Main Interface (Light Mode)
*(Placeholder: Insert screenshot of the application running in Light Mode here)*

### Main Interface (Dark Mode)
*(Placeholder: Insert screenshot of the application running in Dark Mode here)*

### Price History Graph
*(Placeholder: Insert screenshot of the graph dialog showing a stock's trend)*

# 11. References

1.  **Java Documentation:** [https://docs.oracle.com/en/java/](https://docs.oracle.com/en/java/) - For Swing and standard library reference.
2.  **Alpha Vantage API:** [https://www.alphavantage.co/documentation/](https://www.alphavantage.co/documentation/) - For API endpoint details.
3.  **JSON-Java (org.json):** [https://github.com/stleary/JSON-java](https://github.com/stleary/JSON-java) - Library used for JSON parsing.
4.  **GeeksForGeeks:** [https://www.geeksforgeeks.org/java/](https://www.geeksforgeeks.org/java/) - Reference for specific Java implementation details.

