#pragma once
#include "Utils.h"
static const int max_menu_item = 8;
void Run();

int		Select(int max_item = max_menu_item);
void	PrintMenu();

void	TaskNewDay(CityMarket& market);

void	update_supply(CityMarket& market);
void	add_product(CityMarket& market);
void	print_price(CityMarket& market);
void	print_products(CityMarket& market);
void	load_market(CityMarket& market);
void	clear_market(CityMarket& market);
void	profit_products(CityMarket& market);

static std::string menu_exit("0 - Выход");
static std::string please_input("--> ");
static std::string differ("\t---\t---\t---");

static std::string main_menu("\t- Рынок города N - ");
static std::string sub_menu("\t** поведение рынка перед новым днем");

static std::string main_menu1("1 - Новый день...");
static std::string main_menu2("2 - Пополнение складов...");
static std::string main_menu3("3 - Добавить продукт");
static std::string main_menu4("4 - Узнать цену продуктов");
static std::string main_menu5("5 - Посмотреть имеющися продукты");
static std::string main_menu6("6 - Загрузить данные о продуктах из файла");
static std::string main_menu7("7 - Очистить данные о продуктах...");
static std::string main_menu8("8 - Самые прибыльные продукты...");

static std::string sub_menu1("1 - Изменить уровень потребления города");
static std::string sub_menu2("2 - Продать товары со слишком высокой ценой");
static std::string sub_menu3("3 - Смоделировать изменение рыночного предложения конкурентов");
static std::string sub_menu0("0 - Рынок без изменений");


