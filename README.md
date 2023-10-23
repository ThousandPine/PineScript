# Pine Script

## 简介

Pine Script是一个基于解释器运行的脚本语言，其语法参考自Rust，JavaScript，C++等语言

采用类型标注的运行时类型检查，支持左值引用和函数递归调用，暂不支持数组、指针和自定义数据类型

## 构建&运行方式



## 代码样例



## 数据类型

### 类型说明

| 数据类型 | 数据范围 |
| -------- | -------- |
| int      |          |
| float    |          |
| char     |          |
| string   |          |
| bool     |          |
| void     |          |

### 运算符表

运算符优先级从左到右下降

每种数据类型都只能和相同类型进行运算，和其他类型进行运算则需要使用类型转换语法

| 数据类型\运算符 | !    | as   | *    | /    | %    | +    | -    | >    | <    | >=   | <=   | ==   | !=   | =    |
| --------------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| int             |      | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    |
| float           |      | ✔    | ✔    | ✔    |      | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    |
| char            |      | ✔    |      |      |      |      |      | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    |
| string          |      | ✔    |      |      |      | ✔    |      |      |      |      |      | ✔    | ✔    | ✔    |
| bool            | ✔    | ✔    |      |      |      |      |      |      |      |      |      | ✔    | ✔    | ✔    |
| void            |      |      |      |      |      |      |      |      |      |      |      |      |      |      |

### 类型转换表

| 源类型\目标类型 | int  | float | char | string | bool | void |
| --------------- | ---- | ----- | ---- | ------ | ---- | ---- |
| int             | ✔    | ✔     | ✔    | ✔      | ✔    |      |
| float           | ✔    | ✔     | ✔    | ✔      | ✔    |      |
| char            | ✔    | ✔     | ✔    | ✔      | ✔    |      |
| string          |      |       |      | ✔      |      |      |
| bool            | ✔    | ✔     | ✔    | ✔      | ✔    |      |
| void            |      |       |      |        |      |      |



## 语法

### 基本内容

- 每个语句以分号为结束符
- 函数需要在使用前定义（暂不支持函数声明）

### 作用域

```
{
	statements
}
```

通过{}创建一块新的作用域

### 定义变量

```
let NAME: TYPE = VALUE;
let NAME: TYPE;
let NAME = VALUE;
```

基本语法形式参考Rust和JS，每行let语句只能定义一个变量

支持Shadowing，同作用域内可重复定义刷新

### 左值引用

```
let &NAME: TYPE = variable;
let &NAME = variable;
```

语法与定义变量基本相同，主要是在let和NAME之间加了个&符号，并且等号右侧必须为变量

### 定义函数

```
fn FNAME(NAME1: TYPE, &NAME2: TYPE, ...) -> TYPE {
	STATEMENTS
}
```

同样支持使用&定义参数的左值引用，不可嵌套定义，不支持重载

### 类型转换

```
VALUE as TYPE
VALUE as TYPE_1 as TYPE_2 ...
```

### 控制流语句（待实现）

#### if-else

```
if (condition) {
	STATEMENTS
} else if (condition) {
	STATEMENTS
} else if (condition) {
	STATEMENTS
} else {
	STATEMENTS
}
```

#### while

```
while (condition) {
	STATEMENTS
}
```

condition为bool类型表达式

### 输入&输出

```
input `expr1, expr2, ...`
output `expr1, expr2, ...`
```

其中input里的表达式必须能返回左值（当前能返回左值的表达式就只有变量名）

