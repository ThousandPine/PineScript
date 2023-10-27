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
make build 	// 生成带有-O2优化的release版本(pine)
make debug 	// 生成带有-g选项的debug版本(pine.d)
```

## 运行

```
./pine 	src_path
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
        return 0;
    else if(n == 1)
        return 1;
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

## 数据类型

### 类型说明

| 数据类型 | 说明                     |
| -------- | ------------------------ |
| int      | 32位整型                 |
| float    | 32位浮点                 |
| char     | 单字节字符，支持转义字符 |
| string   | 字符串，支持转义字符     |
| bool     | true false               |
| array    | 数组，支持多维嵌套       |
| void     | 无                       |

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

- 语句结束符为`;`
- 支持单行注释`//`和块注释`/* */`
- 程序入口函数为`main`

### 作用域

```
{
	statements
}
```

通过`{}`创建一块新的作用域

### 定义变量

```
let name: type = value; // type不包括void
let name = value;		// 根据value自动推导类型
```

每行let语句只能定义一个变量，并且必须初始化

**支持Shadowing，同作用域内可重复定义变量**

```
/* 样例 */
let a:int = 0;		// 创建int变量并初始化为0
let b = true;		// 自动推导为bool类型
let a:char = '\n';  // Shadowing重定义
```

### 数组

```
/* 字面量 */
[value; size] // value可以是数组的字面量，可以嵌套定义为多维数组
/* 样例 */
let name = [0;5];     		 // 定义一个初始值为5个0的int数组
let name: array = [2.33;5];	 // 定义一个初始值为5个2.33的float数组
let name: array = [[0;5];5]; // 定义一个size为5x5的int数组
```

为了防止出现循环引用，数组**定义后**只能对基本单元进行赋值和修改，不能对数组本身进行赋值操作（比如把一个数组赋值给另一个数组）。

### 左值引用 

定义变量和声明函数参数时，在变量名之间加上`&`即可创建左值引用。

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

### 定义函数

```
fn fun(arg1: type, arg2: type, ...) -> type {
	STATEMENTS
}
```

只能在全局作用域定义，返回类型包括`void`

```
fn max(x: int, y: int) -> int {
	if (x >= y)
		return x;
	else
		return y;
}
```

### 类型转换

```
value as type				  // 转换类型不包括void
value as type_1 as type_2 ... // 支持连续转换
```

```
let a:int = 1e5 as int;	// 将float转为int之后才能合法地赋值
```

### 控制流语句

语法与C语言相同

condition的结果必须为bool类型

#### if-else

```
if (condition)
	statement
else
	statement
```

#### while

```
while (condition) 
	statement
```

### 输入&输出

```
input `arg1, arg2, ...`
output `arg1, arg2, ...`
```

参数列表的两侧为反引号

