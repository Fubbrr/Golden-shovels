# Golden-shovels项目说明文档

> 同济大学软件学院2023年程序设计范式课程期末项目

## 一、项目信息

- 项目选题：**金铲铲之战（2D）**
- 项目GitHub地址：[https://github.com/Qinghanhhh/Golden-shovels](https://github.com/Qinghanhhh/Golden-shovels)
- 选用引擎：**Cocos2d-x 3.17**
- 辅助软件：Photoshop 2022，csm-3d，VS 2022
- 支持平台：Windows

### 成员分工及贡献占比
---

| 姓名     | 学号    |  贡献比  | 课程教师   |
| ------   | ------  |  ------- | ------     |
| **陈雅瑄** | **2250934** | **25%**      | **韩丰夏老师** |
| 罗诗雨   | 2251926 | 25%      | 韩丰夏老师 |
| 付柏瑞   | 2252426 | 25%      | 朱宏明老师 |
| 杨博萱   | 2253220 | 25%      | 韩丰夏老师 |

### 期末项目进度

---

| 时间段                | 进度                                                      |
| --------------------- | -------------------------------------------------------   |
| 2023.11.20-2023.11.30 | 确定小组成员和组长，确定项目选题和使用引擎，熟悉金铲铲游戏   |
| 2023.12.01-2023.12.10 | 学习cocos-2d的相关知识和C++相关知识   |
| 2023.12.10-2023.12.15 | 初步确定项目分工和类的继承关系   |
| 2023.12.16-2023.12.20 | 初步完成界面，英雄及其战斗，商店和战斗准备的类   |
| 2023.12.21-2023.12.24 | 添加音乐，连接类，继续分工进行下一步工作   |
| 2023.12.25-2023.12.27 | 完成小小英雄，经验金币，添加了战斗的回合   |
| 2023.12.28-2023.12.31 | 完成AI和联机，修改一些bug，完善项目   |

## 二、实现的功能

### 基础功能
 1. 有初始界面和设置界面
2. 1v1地图
 3. 支持设置功能，背景音乐的滑动调节和打开关闭
4. 支持多种类型的卡牌，包括战士，辅助，法师和射手
 5. 支持购买卡牌
 6. 支持卡牌升星功能
 7. 支持小小英雄的移动和血量展示
  8. 场上卡牌支持红蓝血条，辅助在蓝条满时可以释放技能，   进行全队回血
  9. 支持练习模式（即单人模式），玩家可以和AI玩家对弈
  10.支持二人联机
  11.支持创建和加入房间

### 拓展功能
1. 实现了战斗时的打斗音效，成功和失败的音效，按键音效。
2. 回合结束会按照剩余英雄的数量进行小小英雄的扣血，增加玩家经验和金币
3. 游戏结束可显示游戏胜利，失败并且有音效
4. 支持玩家经验升级，和可以上场的英雄数量相关
5. 支持卡池和刷新商店卡牌

  ## 三、游戏整体结构设计
  --- 
<img width="991" alt="b6b6017a3f05d450cb5a193744ddf8a" src="https://github.com/Qinghanhhh/Golden-shovels/assets/140044244/5f197418-e868-44e6-8d89-e3080e55350e">

  ## 四、项目亮点

  ### 版本控制和团队协作
  ---
  1. 合理使用Git控制版本，将项目开源至GitHub,保存了多次提交记录
  2. 团队成员分工合理平等，大家互相帮助，合作完成项目
 
  ### 功能和架构
  ---
  1. 界面精美，每个英雄使用AI建模，保证它的的移动和攻击动作会进行变化，而且攻击效果都不同，实现了动画效果，同时使用了AI生成的相关图片，保证界面风格统一
 2. 游戏英雄有大招功能和动画效果，可以造成更高的伤害或回血。
 3. 项目目录结构清晰，清晰介绍成员分工，功能以及架构结构等
 4. 实现了购买的卡池逻辑
 5. AI的水平较高，可以实现较好的练习效果
 6.  经验升级和可以上场的英雄数量相关
 7. 回合结束会按照剩余英雄的数量进行小小英雄的扣血，增加玩家经验和金币
 8. 游戏的英雄的血量，魔力，攻击力，攻击速度，防御，攻击范围，移动速度和攻击速度均有差别，数值会随卡牌升星而升级，且数值设置合理，保证了游戏的可玩性和平衡性
 9. 能显示回合数
 10. 能暂停游戏
 11. 小小英雄右键移动，不会产生冲突


  ### C++规范性
  ---
  1. 基本运用了统一的命名方式
  2. 类的继承和复用合理高效
  3. 运行游戏时不会发生崩溃情况

 ### 资源展示

 **丰富的图片资源**
 ![image](https://github.com/Qinghanhhh/Golden-shovels/assets/140044244/53f79703-a723-414c-8786-864b3ed16eb0)

 **详尽平衡的英雄数值和技能设定**  
示例：   
![image](https://github.com/Qinghanhhh/Golden-shovels/assets/140044244/229a6639-2673-468a-8f56-c6aab8371834)


  

  
  

  
