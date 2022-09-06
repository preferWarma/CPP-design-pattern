/**
 * @file 工厂方法模式.cpp
 * @author https://zhuanlan.zhihu.com/p/83535678
 * @brief
 * 组成:
	1. 抽象工厂类：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
	2. 具体工厂类：继承于抽象工厂，实现创建对应具体产品对象的方式。
	3. 抽象产品类：它是具体产品继承的父类（基类）。
	4. 具体产品类：具体工厂所创建的对象，就是此类。
 * 特点:
	1.工厂方法模式抽象出了工厂类，提供创建具体产品的接口，交由子类去实现。
	2.工厂方法模式的应用并不只是为了封装具体产品对象的创建，而是要把具体产品对象的创建放到具体工厂类实现。
 * 缺陷:
	1.每新增一个产品，就需要增加一个对应的产品的具体工厂类。相比简单工厂模式而言，工厂方法模式需要更多的类定义。
	2.一条生产线只能一个产品。
 * @date 2022-09-06
 */

#include <iostream>

// 抽象产品类
class Shoes
{
public:
	virtual void show() = 0;
	virtual ~Shoes() {}
};

// 耐克球鞋
class NikeShoes : public Shoes
{
public:
	void show() override
	{
		std::cout << "耐克球鞋, 广告语是: Just Do it" << std::endl;
	}

	~NikeShoes()
	{
		std::cout << "NikeShoes 已卖出" << std::endl;
	}
};

// 阿迪达斯球鞋
class AdidasShoes : public Shoes
{
public:
	void show() override
	{
		std::cout << "阿迪达斯球鞋, 广告语是: Impossible is nothing" << std::endl;
	}

	~AdidasShoes()
	{
		std::cout << "AdidasShoes 已卖出" << std::endl;
	}
};

// 李宁球鞋
class LiNingShoes : public Shoes
{
public:
	void show() override
	{
		std::cout << "李宁球鞋, 广告语是: Everthing is possible" << std::endl;
	}

	~LiNingShoes()
	{
		std::cout << "LiNingShoes 已卖出" << std::endl;
	}
};

// 抽象工厂类
class ShoesFactory
{
public:
	virtual Shoes *CreateShoes() = 0;
	virtual ~ShoesFactory() {}
};

// 耐克工厂生产链
class NikeProudcer : public ShoesFactory
{
public:
	Shoes *CreateShoes() override
	{
		return new NikeShoes();
	}
};

// 阿迪达斯工厂生产链
class AdidasProudcer : public ShoesFactory
{
public:
	Shoes *CreateShoes() override
	{
		return new AdidasShoes();
	}
};

// 李宁工厂生产链
class LiNingProudcer : public ShoesFactory
{
public:
	Shoes *CreateShoes() override
	{
		return new LiNingShoes();
	}
};

int main()
{

	// ================ 生产耐克流程 ==================== //
	// 鞋厂开设耐克生产线
	ShoesFactory *nikeFactory = new NikeProudcer();
	// 生产耐克球鞋
	Shoes *nikeShoes = nikeFactory->CreateShoes();
	// 耐克球鞋上市
	nikeShoes->show();
	// 释放资源
	delete nikeFactory;
	nikeFactory = nullptr;
	delete nikeShoes;
	nikeShoes = nullptr;

	// ================ 生产阿迪达斯流程 ==================== //
	// 鞋厂开设阿迪达斯生产线
	ShoesFactory *adidasFactory = new AdidasProudcer();
	// 生产阿迪达斯球鞋
	Shoes *adidasShoes = adidasFactory->CreateShoes();
	// 阿迪达斯球鞋上市
	adidasShoes->show();
	// 释放资源
	delete adidasFactory;
	adidasFactory = nullptr;
	delete adidasShoes;
	adidasShoes = nullptr;

	// ================ 生产李宁流程 ==================== //
	// 鞋厂开设李宁生产线
	ShoesFactory *liNingFactory = new LiNingProudcer();
	// 生产李宁球鞋
	Shoes *liNingShoes = liNingFactory->CreateShoes();
	// 李宁球鞋上市
	liNingShoes->show();
	// 释放资源
	delete liNingFactory;
	liNingFactory = nullptr;
	delete liNingShoes;
	liNingShoes = nullptr;

	return 0;
}