# Interactive Graph Visualizer (`VizualizatorGrafuri`)

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Framework](https://img.shields.io/badge/Graphics-SFML_3.1.0-green.svg)](https://www.sfml-dev.org/)
[![Build System](https://img.shields.io/badge/Build-CMake_3.28%2B-orange.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-purple.svg)](#license)

An interactive, real-time graph visualization application built in **Modern C++ (C++17)** using the **SFML 3.x** graphics library. This project was developed as a demonstration of software engineering best practices, showcasing **Object-Oriented Design (OOP)**, **robust memory management (RAII & Smart Pointers)**, **custom event dispatching**, and visual representations of core **graph traversal and pathfinding algorithms**.

---

## 🚀 Key Architectural & C++ Highlights

This project was structured to reflect standard production-grade C++ guidelines, specifically targeting memory safety, architectural decoupling, and clean design patterns.

### 1. Object-Oriented Design (OOP) & Polymorphism
The design features deep separation of concerns between application execution, event management, graph data structures, and drawing modules:
*   **Abstract Interface & Polymorphism**: A core base class `Graf` defines graph behaviors. Specific behaviors for directed and undirected graphs are encapsulated in `GrafOrientat` and `GrafNeorientat` by overriding key primitives like `AdaugaMuchie`, `StergeMuchie`, and `GetMuchie`:
    ```cpp
    // Base Class Interface
    class Graf {
    public:
        virtual void AdaugaMuchie(int idNod1, int idNod2, int cost) = 0;
        virtual void StergeMuchie(int idNod1, int idNod2) = 0;
        virtual Muchie& GetMuchie(int idNod1, int idNod2) = 0;
        // ...
    };

    // Subclass Customizations
    class GrafOrientat : public Graf {
    public:
        void AdaugaMuchie(int nodStart, int nodEnd, int cost) override;
        // ...
    };
    ```
*   **Custom GUI Elements via SFML Draw Interface**: UI components like `Buton`, `Meniu` (and its submenus: `MeniuInitial`, `MeniuStanga`, `MeniuDreapta`), `Nod`, and `Muchie` inherit from `sf::Drawable` and override `draw()`. This integrates seamlessly with SFML's rendering subsystem, enabling polymorphic window rendering calls (`window.draw(element)`).

### 2. Smart Memory Management & RAII
Memory leaks and dangling pointers are eliminated by design through modern C++ ownership models:
*   **Automatic Lifetimes & Zero Raw Owning Pointers**: Dynamic elements like the active graph instance (`G`) and the event manager (`inputManager`) are owned via unique pointers (`std::unique_ptr`), ensuring resources are automatically reclaimed when contexts change or the application terminates:
    ```cpp
    class Aplicatie {
        sf::RenderWindow window;
        std::unique_ptr<Graf> G;
        std::unique_ptr<ManagerEvenimente> inputManager;
        // ...
    };
    ```
*   **STL Containers**: Nodes (`std::vector<Nod>`), edges (`std::vector<Muchie>`), and adjacency lists are stored in standard collections, leveraging internal allocator RAII guarantees.
*   **Asset Management**: Fonts and textures are loaded via RAII, preventing resource leaks on initialization failures.

### 3. Visual Traversal Decoupling (Lambda Callbacks)
A significant engineering challenge in visual algorithms is running step-by-step algorithms without freezing the rendering loop or duplicating rendering code inside the search logic. 

This is solved by injecting a generic **rendering callback** (`std::function<void()>& renderScene`) into the algorithm methods:
```cpp
void Graf::DFS(int nod, const std::function<void()>& renderScene) {
    vizitat[nod] = 1;
    noduri[nod - 1].SetCuloareNod(CURENT);
    renderScene(); // Triggers a redraw of the window state
    sf::sleep(sf::milliseconds(500)); // Visual pause for the user

    for (const auto& i : matrix[nod]) {
        if (vizitat[i.first] == 0) {
            DFS(i.first, renderScene);
            // ...
        }
    }
}
```
This decouples the visual update mechanism from the graph logic, making the graph class highly reusable and algorithm implementation clear.

### 4. Modern SFML 3.x Monadic Event Handling
The project utilizes the new type-safe event loop API in **SFML 3.x** instead of the older class-based structure. Events are retrieved as variant wrappers, and checked using `.getIf<T>()`:
```cpp
if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseClicked->button == sf::Mouse::Button::Left) {
        float x = static_cast<float>(mouseClicked->position.x);
        float y = static_cast<float>(mouseClicked->position.y);
        // Dispatch actions...
    }
}
```

---

## 🧠 Algorithmic Suite

The application implements and visualizes four core graph operations, displaying node search states dynamically (e.g., Unvisited, Selected, Active, Visited) alongside current path costs:

1.  **DFS (Depth-First Search)**: A recursive traversal algorithm highlighting backtracks.
2.  **BFS (Breadth-First Search)**: A queue-driven traversal visualizing wave expansion.
3.  **Dijkstra's Shortest Path**: Solves the single-source shortest path problem. Employs a `std::priority_queue` as a min-heap utilizing a custom comparator struct (`compareCost`) to evaluate node weights:
    ```cpp
    struct compareCost {
        bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second > b.second; // Min-heap behavior
        }
    };
    ```
4.  **A* Search**: Pathfinding algorithm that uses Dijkstra's base but integrates an **Euclidean Distance Heuristic** calculated dynamically from nodes' screen positions:
    $$\text{Heuristic}(n) = \sqrt{(x_n - x_{dest})^2 + (y_n - y_{dest})^2}$$

---

## 🛠️ Features & Controls

The visualizer supports full graph editing and pathfinding executions.

| Action | Control Mode / Hotkey | Description |
|---|---|---|
| **Add Node** | Left Click on Canvas | Spawn a new numbered node. Prevents overlaps automatically. |
| **Add Edge** | Select "Add Edge" & Click Node 1 &rarr; Node 2 | Connect nodes. Creates undirected or directed edge based on graph type. Default weight is 1. |
| **Custom Weights**| Select "Add Cost" & Click Node 1 &rarr; Node 2 | Opens an overlay. Type the desired cost in the input box and press `Enter`. |
| **Delete Node / Edge** | Select "Delete Node" / "Delete Edge" | Remove elements dynamically; clean-up algorithms run in $O(V+E)$ time. |
| **Move Node** | Select "Move Node" & Drag Node | Drag nodes anywhere in the workspace. Edges automatically adapt. |
| **Reset Graph Mode** | Press `Z` | Deletes the graph and returns to the Main Menu. |
| **Exit Visualizer** | Press `X` or Close Button | Terminate the application safely. |

---

## ⚙️ Compilation & Setup

### Prerequisites
*   **C++ Compiler**: A compiler supporting C++17 or newer (MSVC 2022, GCC 9+, or Clang 10+).
*   **CMake**: Version 3.28 or higher.
*   **SFML 3.x**: Automatically handled via CMake's `FetchContent` module (requires internet access during the initial configuration).

### Step-by-Step Build Instructions

1.  **Clone the Repository**:
    ```bash
    git clone https://github.com/yourusername/vizualizator_grafuri.git
    cd vizualizator_grafuri
    ```

2.  **Ensure Font File**: 
    An `ARIAL.TTF` font file is required by the engine. Ensure this file is placed in the project directory or compiled output folder where the binary runs.

3.  **Generate Build Files & Compile**:
    Using CMake CLI:
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    ```

4.  **Run the Executable**:
    The compiled binary will be placed inside `build/bin/`. Run the executable:
    ```bash
    ./bin/main
    ```

---

## 📂 Project Structure

```
vizualizator_grafuri/
├── CMakeLists.txt            # Declares project dependencies & builds using FetchContent
├── ARIAL.TTF                 # Standard font file for UI and Cost text
├── include/                  # Header declarations
│   ├── aplicatie.h           # Main Application Engine
│   ├── buton.h               # Custom GUI Button representation
│   ├── graf.h                # Graph Base Class & Subclass declarations
│   ├── manager_evenimente.h  # State and event router for mouse/keyboard inputs
│   ├── meniu.h               # Menu interfaces (Drawable)
│   ├── muchie.h              # Edge drawing class with weight text
│   ├── nod.h                 # Node drawing class with dynamic state coloring
│   └── util.h                # State enums & layout constants
└── src/                      # Source implementations
    ├── main.cpp              # Entry point
    ├── aplicatie.cpp         # Main application loop
    ├── buton.cpp             # Button functionality
    ├── graf.cpp              # Base & derived graph behavior + traversal algorithms
    ├── manager_evenimente.cpp# Mouse click and keyboard input state machines
    ├── meniu.cpp             # Submenu logic and coordinate mappings
    ├── muchie.cpp            # Edge calculations (trigonometry for directed arrows)
    └── nod.cpp               # Circle and hover effects logic
```

---

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.