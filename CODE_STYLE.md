# CODE STYLE

> This file describe code style for **pandora** project, because of differences
> between **C** and **C++**, the project allow two code style.

## Chracter Case

- Function

If a C++ function lives in global or namespace level scope, its name should
begin with an upper case character with `CamelCase` style. If a C function,
its name should be `Underscore` style.

- Class

Class name should be upper character with `CamelCase` style.

- Method

Method means C++ functions but lives in class scope. It should use lower case
character as beginning with `CamelCase` style.

Remember, if its parameter is abbreviate form, it should use `CamelCase` style
with upper case as its beginning. If its parameter is full name, use
`Underscore` style without upper case character.

- Variable

Some rule with arguments.

- Struct

In **C++**, `class` is same as `struct` except the default accessibility. So use
`class` as object for OOP, use `struct` as data set. Naming style same with
`class`.
