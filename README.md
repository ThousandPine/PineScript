# Pine Script

## 简介

Pine Script是一个基于解释器运行的脚本语言，其语法参考自Rust，JavaScript，C++等语言

采用类型标注的运行时类型检查，支持左值引用，暂不支持指针和自定义数据类型

由于大部分语法都参考自Rust，因此你可以直接将源文件后缀改为.rs来获得Rust的语法高亮（逃

## 构建

#### 构建环境

OS: Arch Linux x86_64

Kernel: 5.15.90.1-microsoft-standard-WSL2

GCC: 13.2.1

Flex: 2.6.4

Bison: 3.8.2

#### 构建命令

```
make build  // 生成带有-O2优化的release版本(pine)
make debug  // 生成带有-g选项的debug版本(pine.d)
```

## 运行

```
./pine src_path
```

传入源文件路径参数执行，暂时只支持单文件

debug目标则是`./pine.d`

## 代码样例

```rust
/*  样例：递归+记忆化计算斐波那契数列 */

let size = 1 + 1e5 as int;
let vis = [false; size];    // 记录访问
let mem = [0; size];        // 记录结果

fn fib(n:int) -> int {
    if (vis[n])
        return mem[n];
    vis[n] = true;

    if(n == 0)
        return mem[n] = 1;
    else if(n == 1)
        return mem[n] = 1;
    else
        return mem[n] = fib(n - 1) + fib(n - 2);
}

fn main() -> int {
    let a = 233;
    input `a`;
    output `fib(a)`;
    return 0;
}
```

```rust
/* 
 样例：简单DP算法
 P1216 [USACO1.5] [IOI1994]数字三角形 Number Triangles 
 https://www.luogu.com.cn/problem/P1216
*/

let size = 1 + 1e3 as int;
let dp = [[0; size]; size];

fn max(a: int, b: int) -> int {
    if (a >= b)
        return a;
    return b;
}

fn main() -> int {
    let n = 0;
    let ans = 0;
    input `n`;

    let i = 1;
    while (i <= n)
    {
        let j = 1;
        while (j <= i)
        {
            input `dp[i][j]`;
            dp[i][j] = dp[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j]);
            ans = max(dp[i][j], ans);
            j = j + 1;
        }
        i = i + 1;
    }

    output `ans`;
    return 0;
}
```

## 语法

### 数据类型

| 数据类型 | 说明                     |
| -------- | ------------------------ |
| int      | 32位有符号整型           |
| float    | 32位单精度浮点数         |
| char     | 单字节字符，支持转义字符 |
| string   | 字符串，支持转义字符     |
| bool     | true\|false              |
| array    | 数组，支持多维嵌套       |
| void     | 无                       |

### 运算符

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

除了表格中的运算符以外，还支持`+=`, `-=`, `*=`, `/=`, `%=`的赋值运算符，其优先级与`=`相同。

### 基本内容

- 语句结束符为`;`
- 支持单行注释`//`和块注释`/* */`
- 程序入口函数为`main`

### 定义变量

每个let语句只能定义一个变量，并且必须初始化

```
let name: type = expression; // type不包括void
let name = expression;       // 根据expression自动推导类型
```

**支持Shadowing，同作用域内可重复定义变量**

```
let a:int = 0;      // 创建int变量并初始化为0
let b = true;       // 自动推导为bool类型
let a:char = '\n';  // Shadowing重定义
```

### 数组定义

通过`[expression; size]`的形式定义数组的字面量，其中的`expression`的值也可以是数组，以此来嵌套定义多维数组

```
let arr = [0; 5];             // 定义一个初始值为5个0的int数组
let arr: array = [2.33; 5];   // 定义一个初始值为5个2.33的float数组
let arr: array = [[0; 5]; 5]; // 定义一个size为5x5的int数组
```

为了防止出现循环引用，数组**定义后**只能对基本单元进行赋值和修改，不能对数组本身进行赋值操作（比如把一个数组赋值给另一个数组）

```
let a = [[0; 5]; 5];

a[0][0] = 1;   // success
a[0] = [1; 5]; // <error> type 'array' does not support '=' operations with 'array'
```

### 类型转换

由于之前的语法中规定了只能在相同的类型之间进行运算，因此就需要类型转换来加强语言的灵活性

类型转换的语法如下

```
expression as type                 // 将expression的类型转为type
expression as type_1 as type_2 ... // 支持连续转换
```

例如将`float`转为`int`

```
let a:int = 1e5 as int; // 将float转为int之后才能合法地初始化int变量
```

类型转换的真值表如下

| 源类型\目标类型 | int  | float | char | string | bool | array | void |
| --------------- | ---- | ----- | ---- | ------ | ---- | ----- | ---- |
| int             | ✔    | ✔     | ✔    | ✔      | ✔    |       |      |
| float           | ✔    | ✔     |      | ✔      |      |       |      |
| char            | ✔    |       | ✔    | ✔      |      |       |      |
| string          |      |       |      | ✔      |      |       |      |
| bool            | ✔    |       |      | ✔      | ✔    |       |      |
| array           |      |       |      |        |      |       |      |
| void            |      |       |      |        |      |       |      |

### 定义函数

只能在全局作用域定义函数，使用`return`语句返回值，返回类型为`void`时可以不用`return`

```
fn func(arg1: type, arg2: type, ...) -> return_type {
    statements
}
```

例如定义`max`函数返回最大值

```
fn max(x: int, y: int) -> int {
    if (x >= y)
        return x;
    else
        return y;
}
```

### 左值引用

该语法参考自C++，定义变量和声明函数参数时，在变量名之间加上`&`即可创建左值引用。

```
let a = 0;
let &b = a; // b是a的引用
```

```
// 基于左值引用的swap函数
fn swap(&a: int, &b: int) -> void {
    let c = a;
    a = b;
    b = c;
    return;
}
```

### 作用域

在`{}`内部创建一个新的作用域

```
{
    statements
}
```

### 控制流语句

包括`if-else`和`while`，语法格式与C语言相同，其中`expression`返回的结果必须为`bool`类型

```
if (expression)
    statement
else if (expression)
    statement
else
    statement
```

```
while (expression)
    statement
```

### 输入&输出

`input`， `output`分别为输入和输出的关键字，使用反引号包裹参数列表，参数之间用逗号分隔

```
input `arg1, arg2, ...`
output `arg1, arg2, ...`
```

例如输入两个数字，并将他们交换后输出

```
let a = 0;
let b = 0;
let c = 0;
input `a, b`;
/* swap a b */
c = a;
a = b;
b = c;
output `a, ' ', b`;
```
