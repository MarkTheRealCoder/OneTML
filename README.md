


# OneTML
A C++ library for generating HTML pages applying DRY principles.


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

### Features
This section will explain with more details the features of the library.
- [Configurations](#configurations)
- [Components](#components)
   - [HTML components](#HTML-components)
   - [JavaScript components](#JavaScript-components)
- [Templates](#templates)
   - [Full page templates](#full-page-templates)
   - [Partial templates](#partial-templates)
- [Variables](#variables)
    - [Static variables](#static-variables)
    - [Dynamic variables](#dynamic-variables)
    - [Constants](#constants)
- [Control flow statements](#control-flow-statements)
    - [Loops](#loops)
    - [If-Elif-Else](#if-elif-else)
    - [Ternary operator](#ternary-operator)


#### Configurations
The library has a configuration file that can be used to set some parameters that will be used by the library.
<br>
The configuration file is a JSON file that must be placed in the root directory of the project.
<br>
The configuration file must be named `onetml.config.json`.
<br>
The configuration file can contain the following parameters:
```JSON
{
    "basedir": "path_to_the_folder_of_this_file",
    "html": {
        "components": "$basedir/path_to_your_html_components_folder",
        "templates": "$basedir/path_to_your_html_templates_folder",
        "outdir": "$basedir/path_to_your_output_folder"
    },
    "js": {
        "components": "$basedir/path_to_your_js_components_folder"
    },
    "constants": {
        "default_propic": "$basedir/path_to_default_propic/default_propic.png"
    }
}
```

#### Components
Components are a way to create reusable pieces of code that can be used in multiple pages.
<br>
There are two types of components: HTML components and JavaScript components.

##### HTML components
HTML components are pieces of HTML code that can be included in other HTML pages.
<br>
An HTML component supports the following features:
- **Variables**: You can use variables inside a component to make it more dynamic.
- **Nested components**: You can include other components inside a component.
- **Control flow statements**: You can use control flow statements inside a component.
- **Placeholders**: You can use placeholders to include other components inside a component from the parent page.

##### JavaScript components
JavaScript components are pieces of JavaScript code that can be included in other HTML pages.
<br>
A JavaScript component differs from an HTML component because it does not support dynamic modifications.
<br>
This sort of component is useful to make your JS code more modular and to avoid repeating code or writing the code directly inside the HTML page.
<br><br>
You can create a component as follows:
```javascript
function myFunction() {
    console.log("Hello, World!");
}

function myOtherFunction() {
    console.log("Hello, World! 2");
}

components = {
    myFunctionComponent: myFunction,
    myOtherFunctionComponent: myOtherFunction,
    initialization: () => {
        document.addEventListener("DOMContentLoaded", () => {
            document.getElementById("myButton").addEventListener("click", myFunction);
        });
    }
};
```
Now that you have created 3 different components inside a JavaScript file you can choose which components must be included in your HTML page.
<br>
This first example shows how to make a button that logs "Hello, World!" in the console when clicked.
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
    </head>
    <body>
        <h1>Hello, World!</h1>
        <button id="myButton" onclick="myFunction()">Click me!</button>
    </body>
    <include component="myFunctionComponent" script></include>
</html>
```
With this code, after the rendering, you will get the following page:
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
    </head>
    <body>
        <h1>Hello, World!</h1>
        <button id="myButton" onclick="myFunction()">Click me!</button>
    </body>
    <script>
        function myFunction() {
            console.log("Hello, World!");
        }
    </script>
</html>
```
The `script` attribute is used to specify that the component is a JavaScript component.
<br>
Now let's see how to avoid to write the `onclick` attribute in the button tag.
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
    </head>
    <body>
        <h1>Hello, World!</h1>
        <button id="myButton">Click me!</button>
    </body>
    <include component="myFunctionComponent" script></include>
    <include component="initialization" script></include>
</html>
```
With this code, after the rendering, you will get the following page:
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
    </head>
    <body>
        <h1>Hello, World!</h1>
        <button id="myButton">Click me!</button>
    </body>
    <script>
        function myFunction() {
            console.log("Hello, World!");
        }
        document.addEventListener("DOMContentLoaded", () => {
            document.getElementById("myButton").addEventListener("click", myFunction);
        });
    </script>
</html>
```
As you can see, the `initialization` component is used to add an event listener to the button element.
<br>
This code shows that a lambda function gets translated directly into executable code, removing the lambda wrapper syntax.
<br>
Anonymous functions are not supported in this version of the library.

#### Templates
A template is a generic name given to any piece of code that needs to be processed before being sent to the final user.
<br>
There are two types of templates: full page templates and partial templates.

##### Full page templates
A full page template is an HTML page that represents, after the rendering process, a complete HTML page.
<br>
This type of template is useful when you want to send to the user a complete HTML page, like a home page or a contact page
or even something more dynamic like an Amazon cart page.
<br>
This sort of template are not useful when you want to send smaller HTML elements to the user, like the result of an AJAX request.
<br>

##### Partial templates
A partial template is a piece of HTML code that represents, after the rendering process, a part of an HTML page.
<br>
An HTML component, if it's intended to be used as a standalone element, is a partial template.
<br>
Let's make an example:
```HTML
<component name="myComponent">
    <div class="cart-product">
        <img src="%%product_image:string%%" alt="%%product_name:string%%'s image">
        <div class="product-infos">
            <p>%%product_name:string%%</p>
            <p>%%product_description:string%%</p>
        </div>
        <p>%%product_price:float%%</p>
        <input type="number" value="%%product_quantity:int%%" min="1">
    </div>
</component>
```
This component could be used inside a full page template to render a list of products in a cart page.
<br>
But if the cart has too many elements to be rendered in a single call, you can use this component as a partial template 
to render the remaining products with subsequent calls to the server.
<br><br>
With that being said, a partial template and a full page template are not so different, the main difference is the context in which they are used.
<br>
If you want to render a Partial template, from the code perspective, there is a small difference:
```C++
using namespace onetml;

int main() {
    ...
    // Create a new renderer
    Renderer renderer;
    ...
    // Render the HTML page
    HTMLPage page = renderer.render("$myComponent", variables);
    ...
}
```
With the `$` symbol before the component name, you are telling the renderer that it must look for a component with that name instead of a file.






#### Variables
Variables are placeholders for dynamic elements that are not predefined in the HTML code.
<br>
There are two types of variables: static variables and dynamic variables.
<br>
Formally there is no difference between the two types of variables in terms of how they are used and "requested" by the Template/Component.
<br>
The syntax to create/request a variable is the same for both types: `%%variable_name:type%%`.

##### Static variables
A static variable is a variable that is inherited directly from the parent of the component that will use it.
<br>
Just like the variables passed from the renderer, static variables are passed by correspondence (`user_name="John"` &#8594; `%%user_name:string%%`).
<br>
Static variables does not follow the common rules of the type control, every static value is by default a string and every type-control is ignored by default.
<br>
Static variables have low priority over dynamic variables, so if you pass a variable with the same name from the renderer, the static variable will be ignored.
<br>
Static variables are useful in cases where a component needs to be modified to better fit the parent template it refers to:
```HTML
<component name="customHead">
    <title>%%title%%</title> <!-- I don't even specify the type because I know that the title is a static variable -->
    <link rel="stylesheet" href="style.css" type="text/css">
    <meta name="description" content="%%description%%"> <!-- I don't even specify the type because I know that the description is a static variable -->
</component>
```
```HTML
<!DOCTYPE html>
<html>
    <head>
        <include component="customHead" % title="OneTML Example" description="This is an example of a static variable"></include>
    </head>
    <body>
        <h1>Hello, World!</h1>
    </body>
</html>
```
The output will be:
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
        <link rel="stylesheet" href="style.css" type="text/css">
        <meta name="description" content="This is an example of a static variable">
    </head>
    <body>
        <h1>Hello, World!</h1>
    </body>
</html>
```

##### Dynamic variables
A dynamic variable is a variable that is passed from the renderer to the component.
<br>
Dynamic variables are passed by correspondence (`user_name="John"` &#8594; `%%user_name:string%%`).
<br>
Dynamic variables are useful when you need to pass data from the renderer to the template.
<br>
Specifying the type of the variable is optional, but it can be useful to avoid errors in the rendering process.
<br>
Moreover, specifying the type of the variable is required if you want to use custom formatting syntaxes:
```HTML
<!DOCTYPE html>
<html>
    <head>
        <title>OneTML Example</title>
    </head>
    <body>
        <h1>Hello, World!</h1>
        <p>Today: %%today_date:date:'%d-%m-%y'%%</p>
    </body>
</html>
```

##### Constants
Constants are variables that are made globally visible from the configuration file.
<br>
Constants are useful when you need to pass the same value to multiple components or templates.
<br>
Constants are defined in the configuration file as follows:
```JSON
{
    "constants": {
        "default_propic": "default_propic.png"
    }
}
```
Now you can use the `default_propic` constant in your components and templates:
```HTML
<img src="$[default_propic]" alt="Default profile picture">
```

#### Control flow statements
Control flow statements are used to delegate the logic of the rendering process completely to the renderer.
<br>
For example, if you want to specify two different styles of the page based on some values or if you want to repeat a 
piece of code a certain number of times, you can use control flow statements.
<br>
This way you can keep control of what and why is being rendered without trying to figure it out from your code.

##### Loops
Loops are used to repeat a piece of code a certain number of times.
<br>
There is only one type of loop in this version of the library: the `forEach` loop.
<br>
The `forEach` loop is used to iterate over a list of data and create a new component for each element.
<br>
The syntax is the following:
```HTML
%%for $element in $list%%
    <include component="myComponent" % product_name="$element.name" product_price="$element.price"></include>
%%endfor%%
```
This code will render the `myComponent` component for each element in the `list` variable.
<br>
As you can see, instead of using the double percentage `%%` to specify a variable, we used the dollar sign `$`.
<br>
This is because the dollar sign is used to specify that the variable will not be "unpacked" here but will be passed as reference
to the component where the variable will be properly evaluated.
<br>
If you want to ignore the value of each element taken from the list, you can use the following syntax:
```HTML
%%for $_ in $list%%
    <include component="myComponent"></include>
%%endfor%%
```
This will result in repeating the `myComponent` component for each element in the `list` variable without passing any value to it.

##### If-Elif-Else
If-Elif-Else statements are used to create conditional statements to render different components based on the data passed to the renderer.
<br>
The syntax is the following:
```HTML
...
%%if $user_name == "John"%%
    <p>My name is John</p>
%%elif $user_name == "Alice"%%
    <p>My name is Alice</p>
%%else%%
    <p>My name is unknown</p>
%%endif%%
...
```
With these statements you can express any common conditional statement: `==`, `!=`, `>`, `<`, `>=`, `<=` and even check if a value exists: `%%if $user_name%%`.
<br>
The syntax is the same as the one used in the loops, but the `for` keyword is replaced by `if`, `elif` and `else`.
<br>
Every statement must be closed with the `endif` keyword.
<br>
_In future releases there will be the possibility to use custom functions (lambdas) to create more complex conditional statements._

##### Ternary operator
The ternary operator is used to create a conditional statement in a single line.
<br>
This operator is useful when you want to make small changes to an HTML element based on a condition.
<br>
The syntax is the following:
```HTML
<p>My name is %%$user_name == 'John' ? 'John' : 'Alice'%%</p>
```
This code will render the string `'John'` if the `user_name` variable is equal to `'John'`, otherwise it will render the string `'Alice'`.
<br>
The following example will better match the real use case:
```HTML
<img %% $user_propic ? src="$user_propic" : src="$[default_propic]" %% alt="User profile picture">
```
