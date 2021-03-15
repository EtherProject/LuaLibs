# LuaJsonLib

JSON 解析库

## API 总览

|         名称         |                         功能                          |
|:--------------------:|:-----------------------------------------------------:|
|     `value = Load(str)`      |          将已编码的 JSON 对象解码为 Lua 对象          |
| `value = LoadFromFile(path)` |   将指定路径文件中已编码的 JSON 对象解码为 Lua 对象   |
|     `str = Dump(value [, isFormat=false])`      |             将 Lua 对象编码成 JSON 字符串             |
|  `DumpToFile(value, path [, isFormat=false])`  | 将 Lua 对象编码成 JSON 字符串并存储到指定路径的文件中 |

## API 详述

+ ### value = Load(str) 
    - *功能：*  
        将已编码的 JSON 对象解码为 Lua 对象
    - *参数列表：*  
        * str [string]：已编码的 JSON 对象字符串
    - *返回值列表：*  
        * value [nil / boolean / number / string / table]：解码后的 Lua 对象

+ ### value = LoadFromFile(path)  
    - *功能：*  
        将指定路径文件中已编码的 JSON 对象解码为 Lua 对象
    - *参数列表：*  
        * path [string]：存储已编码 JSON 对象的文件路径
    - *返回值列表：*  
        * value [nil / boolean / number / string / table]：解码后的 Lua 对象

+ ### str = Dump(value [, isFormat=false])  
    - *功能：*  
        将 Lua 对象编码成 JSON 字符串
    - *参数列表：*  
        * value [nil / boolean / number / string / table]：Lua 对象
        * isFormat [boolean]：（可选）是否对编码后的字符串格式化，默认不进行格式化
    - *返回值列表：*  
        * str [string]：已编码的 JSON 对象字符串

+ ### DumpToFile(value, path [, isFormat=false])  
    - *功能：*  
        将 Lua 对象编码成 JSON 字符串并存储到指定路径的文件中
    - *参数列表：*  
        * value [nil / boolean / number / string / table]：Lua 对象
        * path [string]：用以存储已编码 JSON 对象的文件路径
        * isFormat [boolean]：（可选）是否对编码后的字符串格式化，默认不进行格式化
    - *返回值列表：*  
        无

## 注意

由于 Lua 语法允许数字索引和字符串索引同处于一个 table 类型的变量中，故当两者并存时，调用 `Dump()` 或 `DumpToFile` 方法会将数字索引转换为对应的字符串索引，如：`ExmpTable = { name = "xiaoming", "Here" }` 在进行编码后对应的 JSON 字符串可能为：`{ "1":	"Here", "name":	"xiaoming" }`  
同样的，在对 JSON 字符串进行解码时，LuaJsonLib 也会优先将可能转换为数字索引的字符串键值转化数字索引存入对应的 table 中  
所以，为避免编码的 JSON 数据与其他程序交互时产生二义性，请尽量避免对同时存在数字索引和字符串索引的 table 类型数据进行编码

## 特别感谢  

+ [cJSON](https://github.com/DaveGamble/cJSON)：为 LuaJsonLib 提供了跨平台的底层实现
