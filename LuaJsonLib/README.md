# LuaJsonLib

JSON 解析库

## API 总览

|         名称         |                         功能                          |
|:--------------------:|:-----------------------------------------------------:|
|     `Load(string:str)`      |          将已编码的 JSON 对象解码为 Lua 对象          |
| `LoadFromFile(string:path)` |   将指定路径文件中已编码的 JSON 对象解码为 Lua 对象   |
|     `Dump(string:str)`      |             将 Lua 对象编码成 JSON 字符串             |
|  `DumpToFile(string:path)`  | 将 Lua 对象编码成 JSON 字符串并存储到指定路径的文件中 |

### 注：功能尚未全部完成！

## 特别感谢  

+ [cJSON](https://github.com/DaveGamble/cJSON)：为 LuaJsonLib 提供了跨平台的底层实现
