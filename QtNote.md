**布局**

**样式**

**信号与槽**

**内存管理方式**

# 基础

## 控件

> 1. label：标签，可以显示文本信息，只读；
> 2. pushbutton ： 普通按钮；
> 3. radiobutton ： 单选按钮，多个单选按钮中只能选择一个，但是必须放入groupbox中，类似单选题；
> 4. checkbox ： 多选复选按钮，可以选择同时选择多个，类似多选题；
> 5. lineedit ： 单行文本编辑框，可以输入单行文本；
> 6. textedit ： 多行文本输入框，可以输入显示多行文本和图片；
> 7. combobox ： 下拉文本输入框，在输入框的最右边有个三角下拉按钮，可以选择输入，也可以手动输入；
> 8. textbrower ： 多行文本显示框，只读；
> 9. groupbox ： 可以在里面放入特点的东西，统一管理；
> 10. slider ： 模拟显示滑动条；
> 11. spinbox ： 数值显示滑动条；
> 12. dateedit ：
> 13. timeedit ：
> 14. datetimeedit ：
> 15. lcdnumber ：

## 布局

#### QHBoxLayout--水平布局

###### addWidget(ptr)

作用为：QHBoxLayout类将控制ptr对应的元素的UI

###### addStretch(int)

“空白占位小弹簧”

#### QVBoxLayout--垂直布局

###### addLayout

对应addWidget(ptr)

#### 常用函数

##### setSpacing()

![image-20231103094235728](QtNote.assets/image-20231103094235728.png)

##### addSpacing()

![image-20231103094314281](QtNote.assets/image-20231103094314281.png)

##### setStretch ( int index, int stretch ) 设置拉伸比例

![image-20231103095945402](QtNote.assets/image-20231103095945402.png)

##### setContentsMargins(int left, int top, int right, int bottom)

![image-20231103100042552](QtNote.assets/image-20231103100042552.png)

#####  QFormLayout 表单布局

![image-20231103100121159](QtNote.assets/image-20231103100121159.png)

##### QGridLayout 网格布局

![image-20231103100144418](QtNote.assets/image-20231103100144418.png)

#####  布局嵌套

![image-20231103100352925](QtNote.assets/image-20231103100352925.png)



##### setLayout

setLayout()的参数为上两个类指针

## 四种模式

![image-20231102145740261](QtNote.assets/image-20231102145740261.png)

## 信号与信号槽

![image-20231102160638157](QtNote.assets/image-20231102160638157.png)

![image-20231102160759606](QtNote.assets/image-20231102160759606.png)

![image-20231102160720546](QtNote.assets/image-20231102160720546.png)

**三者的关系**

# 认识QT

## UI文件设计与运行机制

.pro 项目管理文件

![image-20231102131450636](QtNote.assets/image-20231102131450636.png)

.ui 界面文件

![image-20231102131835987](QtNote.assets/image-20231102131835987.png)

主函数

![image-20231102132649881](QtNote.assets/image-20231102132649881.png)

图形相关文件

![image-20231102132828650](QtNote.assets/image-20231102132828650.png)

![image-20231102132844857](QtNote.assets/image-20231102132844857.png)

.h文件

![image-20231102133229596](QtNote.assets/image-20231102133229596.png)

.cpp

![image-20231102133458963](QtNote.assets/image-20231102133458963.png)

ui\_\*\*_.h

![image-20231102134017595](QtNote.assets/image-20231102134017595.png)

## 可视化UI

### 界面UI

![image-20231102134314273](QtNote.assets/image-20231102134314273.png)

![image-20231102134700001](QtNote.assets/image-20231102134700001.png)

### 三种信号触发方式

###### 第一种

![image-20231102142247015](QtNote.assets/image-20231102142247015.png)

1. 在UI界面选中目标，并右键点击，选择对应函数

![image-20231102142919839](QtNote.assets/image-20231102142919839.png)

![image-20231102143225947](QtNote.assets/image-20231102143225947.png)



2. 编写对应逻辑


   ![image-20231102143018435](QtNote.assets/image-20231102143018435.png)![image-20231102143053026](QtNote.assets/image-20231102143053026.png)

###### 第二种

> 将ui_dialog.h的内容提到cpp文件里

![image-20231102145034090](QtNote.assets/image-20231102145034090.png)

编译生成的ui_dialog.h文件中，有对应的调用函数及逻辑，可将其拷贝修改至CPP文件

![image-20231102145213471](QtNote.assets/image-20231102145213471.png)

![image-20231102145438806](QtNote.assets/image-20231102145438806.png)

可以认为是第一种的手动版，但CPP的文件不会随着ui的改动而变化。

## 代码化UI

![image-20231102150729491](QtNote.assets/image-20231102150729491.png)

没有UI文件，需要自己设计界面，较抽象。

## 混合UI







# 实例

### 场景1

![image-20231103141205368](QtNote.assets/image-20231103141205368.png)

#### 实现

#### 构思

> ![image-20231105220555660](%E5%9B%BE%E7%89%87/QtNote/image-20231105220555660.png)

#### 效果

> 默认
>
> ![image-20231105215059830](%E5%9B%BE%E7%89%87/QtNote/image-20231105215059830.png)

> 拉伸
>
> ![image-20231105215109472](%E5%9B%BE%E7%89%87/QtNote/image-20231105215109472.png)
>
> ![image-20231105215130986](%E5%9B%BE%E7%89%87/QtNote/image-20231105215130986.png)

> 账号按钮
>
> ![image-20231105215155165](%E5%9B%BE%E7%89%87/QtNote/image-20231105215155165.png)

> 隐藏按钮
>
> ![image-20231105212145634](%E5%9B%BE%E7%89%87/QtNote/image-20231105212145634.png)

> 伪类选择器
>
> ![image-20231105215324399](%E5%9B%BE%E7%89%87/QtNote/image-20231105215324399.png)
