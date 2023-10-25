# Pine Script

## 简介

Pine Script是一个基于解释器运行的脚本语言，其语法参考自Rust，JavaScript，C++等语言

采用类型标注的运行时类型检查，支持左值引用和函数递归调用，暂不支持指针和自定义数据类型

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
| array    |          |
| void     |          |

### 运算符表

运算符优先级从左到右下降

每种数据类型都只能和相同类型进行运算，和其他类型进行运算则需要使用类型转换语法

| 数据类型\运算符 | []   | -(minus) | !    | as   | *    | /    | %    | +    | -    | >    | <    | >=   | <=   | ==   | &&   | \|\| | !=   | =    |
| --------------- | ---- | -------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| int             |      | ✔        |      | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    |      |      | ✔    | ✔    |
| float           |      | ✔        |      | ✔    | ✔    | ✔    |      | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    | ✔    |      |      | ✔    | ✔    |
| char            |      |          |      | ✔    |      |      |      |      |      | ✔    | ✔    | ✔    | ✔    | ✔    |      |      | ✔    | ✔    |
| string          |      |          |      | ✔    |      |      |      | ✔    |      | ✔    | ✔    | ✔    | ✔    | ✔    |      |      | ✔    | ✔    |
| bool            |      |          | ✔    | ✔    |      |      |      |      |      |      |      |      |      | ✔    | ✔    | ✔    | ✔    | ✔    |
| array           | ✔    |          |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
| void            |      |          |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |

### 类型转换表

| 源类型\目标类型 | int  | float | char | string | bool | array | void |
| --------------- | ---- | ----- | ---- | ------ | ---- | ----- | ---- |
| int             | ✔    | ✔     | ✔    | ✔      | ✔    |       |      |
| float           | ✔    | ✔     |      | ✔      |      |       |      |
| char            | ✔    |       | ✔    | ✔      |      |       |      |
| string          |      |       |      | ✔      |      |       |      |
| bool            | ✔    |       |      | ✔      | ✔    |       |      |
| array           |      |       |      |        |      |       |      |
| void            |      |       |      |        |      |       |      |



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
let NAME: TYPE = VALUE; // type不包括void
let NAME: TYPE;			// type不包括void
let NAME = VALUE;
```

基本语法形式参考Rust和JS，每行let语句只能定义一个变量

支持Shadowing，同作用域内可重复定义刷新

### 数组

```
/* 字面量 */
[TYPE;size]  // TYPE不能包括array和void
[VALUE;size] // VALUE可以是数组的字面量，即是说可以嵌套定义为多维数组
/* 样例 */
let NAME: array = [int;5];     // 定义一个size为5的int数组
let NAME: array = [2.33;5];	   // 定义一个初始值为5个2.33的float数组
let NAME: array = [[int;5];5]; // 定义一个size为5x5的int数组
// 数组只能在定义时使用赋值，并且默认为引用传递
let a1 = [int;5];
let a2 = a1;		// a2和a1指向同一个数组空间
```

为了防止出现循环引用，数组**定义后**只能对基本单元进行赋值和修改，不能对数组本身进行赋值操作（比如把一个数组赋值给另一个数组）。

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

