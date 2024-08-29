#include "Information.h"
#include<algorithm>

// 在类外初始化静态成员变量
std::map<int, heroInformation> Information::info;

Information::Information() {
	////英雄名map
	//name[0] = "";
	////法师
	//name[1] = "Taric";
	//name[2] = "Ali";
	//name[3] = "Anny";
	//name[4] = "Alice";
	////射手
	//name[5] = "Nami";
	//name[6] = "Erlius";
	//name[7] = "Kasia";
	////辅助（远战）
	//name[8] = "Lilia";
	////辅助（近战）
	//name[9] = "Kuqi";
	////战士
	//name[10] = "Kennen";
	//name[11] = "Chuishi";
	//name[12] = "Serti";
	//name[13] = "Katerina";
	//name[14] = "Evelynn";

	//英雄信息设置
	SetHeroInfo();
}
heroInformation* Information::getheroInformation(int heroTag, int level) {
	// 检查是否存在该英雄的信息
	if (info.find(heroTag) != info.end()) {
		// 获取基础信息
		heroInformation* baseInfo = &info[heroTag];

		// 创建一个新的 heroInformation 对象来存储升级后的属性
	 heroInformation* upgradedInfo = new heroInformation(*baseInfo);

		// 更新属性，这里假设每级增加的属性是固定的
		upgradedInfo->HP += level * 10; // 示例：每级增加10点生命值
		upgradedInfo->attack += level * 5; // 示例：每级增加5点攻击力

		// 返回更新后的英雄信息
		return upgradedInfo;
	}
	return nullptr; // 如果找不到英雄信息，返回 nullptr
}
void Information::SetHeroInfo() {
	///法师类
	//Taric
	heroInformation Taric;
	Taric.HP = 500;
	Taric.MP = 60;
	Taric.attack = 120;
	Taric.atkspeed = 1.3;
	Taric.defence = 25;
	Taric.atkrange = 180;
	Taric.movespeed = 80;
	info[1] = Taric;

	heroInformation Ali;
	Ali.HP = 400;
	Ali.MP = 60;
	Ali.attack = 140;
	Ali.atkspeed = 1.1;
	Ali.defence = 25;
	Ali.atkrange = 200;
	Ali.movespeed = 80;
	info[2] = Ali;

	heroInformation Anny;
	Anny.HP = 550;
	Anny.MP = 70;
	Anny.attack = 135;
	Anny.atkspeed = 1.1;
	Anny.defence = 30;
	Anny.atkrange = 220;
	Anny.movespeed = 80;
	info[3] = Anny;

	heroInformation Alice;
	Alice.HP = 450;
	Alice.MP = 90;
	Alice.attack = 150;
	Alice.atkspeed = 1.0;
	Alice.defence = 35;
	Alice.atkrange = 190;
	Alice.movespeed = 80;
	info[4] = Alice;

	///射手类
	heroInformation Nami;
	Nami.HP = 400;
	Nami.MP = 60;
	Nami.attack = 110;
	Nami.atkspeed = 0.7;
	Nami.defence = 30;
	Nami.atkrange = 250;
	Nami.movespeed = 80;
	info[5] = Nami;

	heroInformation Erlius;
	Erlius.HP = 500;
	Erlius.MP = 90;
	Erlius.attack = 100;
	Erlius.atkspeed = 0.6;
	Erlius.defence = 20;
	Erlius.atkrange = 300;
	Erlius.movespeed = 80;
	info[6] = Erlius;

	heroInformation Kasia;
	Kasia.HP = 450;
	Kasia.MP = 120;
	Kasia.attack = 130;
	Kasia.atkspeed = 0.85;
	Kasia.defence = 35;
	Kasia.atkrange = 260;
	Kasia.movespeed = 80;
	info[7] = Kasia;

	///辅助类
	heroInformation Lilia;
	Lilia.HP = 650;
	Lilia.MP = 80;
	Lilia.attack = 90;
	Lilia.atkspeed = 1.4;
	Lilia.defence = 45;
	Lilia.atkrange = 180;
	Lilia.movespeed = 80;
	info[8] = Lilia;

	heroInformation Kuqi;
	Kuqi.HP = 850;
	Kuqi.MP = 70;
	Kuqi.attack = 70;
	Kuqi.atkspeed = 1.2;
	Kuqi.defence = 55;
	Kuqi.atkrange = 80;
	Kuqi.movespeed = 80;
	info[9] = Kuqi;

	///战士类
	heroInformation Kennen;
	Kennen.HP = 1000;
	Kennen.MP = 90;
	Kennen.attack = 200;
	Kennen.atkspeed = 1.8;
	Kennen.defence = 55;
	Kennen.atkrange = 60;
	Kennen.movespeed = 80;
	info[10] = Kennen;

	heroInformation Chuishi;
	Chuishi.HP = 800;
	Chuishi.MP = 70;
	Chuishi.attack = 190;
	Chuishi.atkspeed = 1.5;
	Chuishi.defence = 50;
	Chuishi.atkrange = 70;
	Chuishi.movespeed = 80;
	info[11] = Chuishi;

	heroInformation Serti;
	Serti.HP = 900;
	Serti.MP = 50;
	Serti.attack = 180;
	Serti.atkspeed = 1.4;
	Serti.defence = 60;
	Serti.atkrange = 60;
	Serti.movespeed = 80;
	info[12] = Serti;

	heroInformation Katerina;
	Katerina.HP = 700;
	Katerina.MP = 50;
	Katerina.attack = 210;
	Katerina.atkspeed = 1.8;
	Katerina.defence = 50;
	Katerina.atkrange = 100;
	Katerina.movespeed = 80;
	info[13] = Katerina;

	heroInformation Evelynn;
	Evelynn.HP = 1000;
	Evelynn.MP = 90;
	Evelynn.attack = 180;
	Evelynn.atkspeed = 1.4;
	Evelynn.defence = 60;
	Evelynn.atkrange = 60;
	Evelynn.movespeed = 80;
	info[14] = Evelynn;
}
std::unordered_map<int, std::string> Information::name = {
	{0, ""},
	{1, "Taric"},
	{2, "Ali"},
	{3, "Anny"},
	{4, "Alice"},
	{5, "Nami"},
	{6, "Erlius"},
	{7, "Kasia"},
	{8, "Lilia"},
	{9, "Kuqi"},
	{10, "Kennen"},
	{11, "Chuishi"},
	{12, "Serti"},
	{13, "Katerina"},
	{14, "Evelynn"}
};


std::unordered_map<int, std::string> Information::imagePaths = {
    {1, "Taric.png"},
    {2, "Ali.png"},
   {3,"Anny.png" },
    {4,"Alice.png"},
	{5, "Nami.png"},
	{6, "Erlius.png"},
	{7, "Kasia.png"},
	{8, "Lilia.png"},
	{9, "Kuqi.png"},
	{10, "Kennen.png"},
	{11, "Chuishi.png"},
	{12, "Serti.png"},
	{13, "Katerina.png"},
	{14, "Evelynn.png"}
};

std::unordered_map<int, std::string> Information::warimagePaths = {
	{1, "Taric-action1.png"},
	{2, "Ali-action1.png"},
   {3,"Anny-action1.png" },
	{4,"Alice-action1.png"},
	{5, "Nami-action1.png"},
	{6, "Erlius-action1.png"},
	{7, "Kasia-action1.png"},
	{8, "Lilia-action1.png"},
	{9, "Kuqi-action1.png"},
	{10, "Kennen-action1.png"},
	{11, "Chuishi-action1.png"},
	{12, "Serti-action1.png"},
	{13, "Katerina-action1.png"},
	{14, "Evelynn-action1.png"}
};

std::string Information::getNameByTag(int tag) {
    return name[tag];
}

std::string Information::getHeroPathByTag(int tag) {
    return imagePaths[tag];
}

heroInformation* Information::GetInfoByTag(int tag) {
	/*heroInformation* testInfo4 = new heroInformation;
	testInfo4->HP = 700;
	testInfo4->MP = 60;
	testInfo4->attack = 60;
	testInfo4->atkspeed = 1.5;
	testInfo4->defence = 35;
	testInfo4->atkrange = 200;
	testInfo4->movespeed = 80;
	info[tag] = *testInfo4;*/
	return &info[tag];
}