


# OneTML
A C++ library to create HTML pages without rewriting not a single piece of code.


### Supported languages
  - [ ] Java 
  - [ ] Python
  - [ ] Javascript/Typescript
  - [x] C
  - [x] C++


### Table of contents
- [Overview](#overview)
- [How to use](#how-to-use)
- [Features](#features)
- [Examples](#examples)


### Overview
This library offers a simple way to create HTML code using _components_, _templates_ and _control flow statements_.
<br>
The main idea is to avoid repeating code and to make the code more readable and maintainable without the need to trade 
off flexibility.
<br><br>
What does this library do to achieve this goal?
- Components: You can create components of both HTML and JavaScript code granting the possibility to be extremely specific on
    what you want in your page.
- Templates: A template is a generic piece of **HTML** code that needs to be processed before being sent to the final user.
- Variables: You can create variables with or without a specific data-type inside HTML code.
    These variables are just placeholders for the data passed from the renderer, but can be used in combination with control flow statements.
- Control flow statements: You can use control flow statements to create dynamic pages, like loops and conditionals.
    - Loops: You can iterate over a list of data and create a new component for each element.
    - If-Elif-Else: You can create conditional statements to render different components based on the data passed to the renderer.
    - Ternary operator: You can use the ternary operator to create a conditional statement in a single line.


### How to use

- [Create a simple HTML page](#create-a-simple-html-page)
- [Create a simple HTML page with a component](#create-a-simple-html-page-with-a-component)
- [Create a simple HTML page with two nested components](#create-a-simple-html-page-with-two-nested-components)
- [Create a simple HTML page with a variable](#create-a-simple-html-page-with-a-variable)
- [Create a simple HTML page with a static variable](#create-a-simple-html-page-with-a-static-variable)
- [Create a simple HTML page with a control flow statement](#create-a-simple-html-page-with-a-control-flow-statement)


#### Create a simple HTML page
1. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
        </body>
    </html>
    ```
2. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html");
        // Now you can send the content of this page to the client converting it in any format you want
        ...
    }
    ```
   If you want to render the page and save it in a specific directory, to make it statically rendered, you can use the following code:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Render the HTML page and save it in a specific directory
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html", "path_to_your_output_folder/index.html");
        ...
    }
    ```
   This second approach can be useful if you want to reduce computation time and make the page static or semi-static (this concept will be explained later).

#### Create a simple HTML page with a component

1. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <include component="myComponent"></include>
        </body>
    </html>
    ```
2. Create a new file called 'myComponent.html' inside a predefined folder defined inside library configs and write the following code:
    ```HTML
    <component name="myComponent">
        <p>This is a component</p>
    </component>
    ```
3. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html");
        ...
    }
    ```

#### Create a simple HTML page with two nested components

1. Create a new file called 'myComponent.html' inside a predefined folder defined inside library configs and write the following code:
    ```HTML
    <component name="myComponent">
        <p>This is a component</p>
        <include placeholder="anotherComponent"></include>
    </component>
   
    <component name="myNestedComponent">
        <p>This is a nested component</p>
    </component>
    ```

2. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <include component="myComponent">
                <into placeholder="anotherComponent">
                    <include component="myNestedComponent"></include>
                </into>
            </include>
        </body>
    </html>
    ```

3. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html");
        ...
    }
    ```
    The output will be:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>This is a component</p>
            <p>This is a nested component</p>
        </body>
    </html>
    ```


#### Create a simple HTML page with a variable

1. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>My name is %%user_name%%</p>
        </body>
    </html>
    ```
   You can even specify a type for the variable for better control over the data passed to the renderer:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>My name is %%user_name:string%%</p>
        </body>
    </html>
    ```
2. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Create a map with the variables you want to pass to the renderer
        std::map<std::string, std::string> variables;
        variables["user_name"] = "John";
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html", variables);
        ...
    }
    ```
    The output will be:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>My name is John</p>
        </body>
    </html>
    ```

#### Create a simple HTML page with a static variable
_Static variables are not visible without using a component.
<br>
Every static value is by default a string and every type-control is ignored by default._

1. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <include component="myComponent" % user_name="John"></include>
        </body>
    </html>
    ```

2. Create a new file called 'myComponent.html' inside a predefined folder defined inside library configs and write the following code:
    ```HTML
    <component name="myComponent">
        <p>My name is %%user_name%%</p>
    </component>
    ```

3. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
   
        std::map<std::string, std::string> variables;
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html", variables);
        ...
    }
    ```
    The output will be:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>My name is John</p>
        </body>
    </html>
    ```

#### Create a simple HTML page with a control flow statement

1. Create a new file called 'index.html' and write the following code:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            %%if $user_name == "John"%%
                <p>My name is John</p>
            %%elif $user_name == "Alice"%%
                <p>My name is Alice</p>
            %%else%%
                <p>My name is unknown</p>
            %%endif%%
        </body>
    </html>
    ```
2. In your C++ code, include the library and render the HTML page as follows:
    ```C++
    using namespace onetml;
   
    int main() {
        ...
        // Create a new renderer
        Renderer renderer;
        
        // Create a map with the variables you want to pass to the renderer
        std::map<std::string, std::string> variables;
        variables["user_name"] = "John";
        
        // Render the HTML page
        HTMLPage page = renderer.render("path_to_your_html_folder/index.html", variables);
        ...
    }
    ```
    The output will be:
    ```HTML
    <!DOCTYPE html>
    <html>
        <head>
            <title>OneTML Example</title>
        </head>
        <body>
            <h1>Hello, World!</h1>
            <p>My name is John</p>
        </body>
    </html>
    ```
