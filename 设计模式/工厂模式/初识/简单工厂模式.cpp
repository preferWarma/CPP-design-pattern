/**
 * @file 简单工厂模式.cpp
 * @author https://zhuanlan.zhihu.com/p/83535678
 * @brief
 * 组成: 1. 工厂类：工厂模式的核心类，会定义一个用于创建指定的具体实例对象的接口。
		 2. 抽象产品类：是具体产品类的继承的父类或实现的接口。
		 3. 具体产品类：工厂类所创建的对象就是此具体产品实例。
 * 特点: 工厂类封装了创建具体产品对象的函数。
 * 缺陷: 扩展性非常差，新增产品的时候，需要去修改工厂类。
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

enum SHOES_TYPE
{
	NIKE,
	LINING,
	ADIDAS
};

// 工厂类
class ShoesFactory
{
public:
	Shoes *CreateShoes(SHOES_TYPE type)
	{
		switch (type)
		{
		case NIKE:
			return new NikeShoes();
			break;
		case LINING:
			return new LiNingShoes();
			break;
		case ADIDAS:
			return new AdidasShoes();
			break;
		default:
			return nullptr;
			break;
		}
	}
};

int main()
{
	// 创建工厂对象
	ShoesFactory shoesFactory;

	// 从工厂对象创建耐克球鞋对象
	Shoes *nikeShoes = shoesFactory.CreateShoes(NIKE);
	if (nikeShoes != nullptr)
	{
		nikeShoes->show();
		// 销毁耐克球鞋对象
		delete nikeShoes;
		nikeShoes = nullptr;
	}

	// 从工厂对象创建李宁球鞋对象
	Shoes *liNingShoes = shoesFactory.CreateShoes(LINING);
	if (liNingShoes != nullptr)
	{
		liNingShoes->show();
		// 销毁李宁球鞋对象
		delete liNingShoes;
		liNingShoes = nullptr;
	}

	// 从工厂对象创建阿迪达斯球鞋对象
	Shoes *adidasShoes = shoesFactory.CreateShoes(ADIDAS);
	if (adidasShoes != nullptr)
	{
		adidasShoes->show();
		// 销毁阿迪达斯球鞋对象
		delete adidasShoes;
		adidasShoes = nullptr;
	}
	return 0;
}