/**
 * @file 模板工厂.cpp
 * @author https://zhuanlan.zhihu.com/p/83537599
 * @brief 模板工厂: 针对工厂方法模式封装成模板工厂类，那么这样在新增产品时，是不需要新增具体的工厂类，减少了代码的编写量
 * @date 2022-09-06
 */

#include <iostream>

// 基类 鞋子
class Shoes
{
public:
	virtual void show() = 0;
	virtual ~Shoes() {}
};

// 耐克鞋子
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

// 基类 衣服
class Clothes
{
public:
	virtual void show() = 0;
	virtual ~Clothes() {}
};

// 优衣库衣服
class UniqloClothes : public Clothes
{
public:
	void show() override
	{
		std::cout << "优衣库衣服, 广告语是: I am Uniqlo" << std::endl;
	}
	~UniqloClothes()
	{
		std::cout << "UniqloClothes 已卖出" << std::endl;
	}
};

// 抽象模板类
// 模板参数 AbstactProduct_t 抽象产品类(如Shoes, Clothes)
template <class AbstactProduct_t>
class AbstractFactory
{
public:
	virtual AbstactProduct_t *CreateProuducer() = 0; // 创建一个的抽象产品生产线, 如Shoes(或Clothes)
	virtual ~AbstractFactory() {}
};

// 具体模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
template <class AbstractProduct_t, class ConcreteProuct_t>
class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
{
public:
	AbstractProduct_t *CreateProuducer() override
	{ // 创建一个具体的产品, 如NikeShoes(或UniqloClothes)
		return new ConcreteProuct_t();
	}
};

int main()
{
	// 创建耐克鞋的工厂对象
	ConcreteFactory<Shoes, NikeShoes> nikeFactory;
	// 生产耐克鞋
	Shoes *nikeShoes = nikeFactory.CreateProuducer();
	// 耐克鞋上市
	nikeShoes->show();

	// 创建优衣库的工厂对象
	ConcreteFactory<Clothes, UniqloClothes> uniqloFactory;
	// 生产优衣库衣服
	Clothes *uniqloClothes = uniqloFactory.CreateProuducer();
	// 优衣库衣服上市
	uniqloClothes->show();

	// 释放资源
	delete nikeShoes;
	nikeShoes = nullptr;
	delete uniqloClothes;
	uniqloClothes = nullptr;

	return 0;
}