# RL Language

## 基本类型

### int

运算类型：四则，比较，取模

运算对象: int

类型转换: float, bool, char

### float

运算类型：四则，比较

运算对象: float

类型转换: int

### char

运算类型：四则，比较

运算对象: char

类型转换: int, string

### string

运算类型：加法，比较

运算对象：string

类型转换：无

### bool

运算类型：比较，取反

运算对象：bool

类型转换：int

### void

运算类型：无

运算对象：无

类型转换：无

## 语法

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

支持Shadowing，同作用域内可重复定义

### 左值引用

```
let &NAME: TYPE = VAR;
let &NAME = VAR;
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

### 基本运算

四则运算，取非，取模，比较，括号，赋值

### 控制流

#### if-else

```
if (VALUE) {
	STATEMENTS
} else if (VALUE) {
	STATEMENTS
} else if (VALUE) {
	STATEMENTS
} else {
	STATEMENTS
}
```

VALUE为bool类型，if后可跟随任意多个else if，并且else if和else可省略

#### while

```
while (VALUE) {
	STATEMENTS
}
```

VALUE为bool类型

### 数组

### 输入&输出





