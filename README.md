# 同步歌词-歌词快速匹配算法

#### 使用示例
```C++
#include <iostream>
#include "ProcessLRC.h"
int main()
{
	ProcessLRC lrc;
	lrc.LoadLRC(string("887902.lrc"));
	cout << "\n";
	cout << lrc.refreshLrc(150).data();
}

```

### LRC 格式歌词 

- 暂时只解析时间部分，作曲作家部分暂时不解析

![](https://github.com/ChunSource/Synchronize-lyrics/blob/master/gc.png?raw=true)



>本算法只是个人写作，不代表最优算法

