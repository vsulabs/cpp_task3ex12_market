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

static std::string menu_exit("0 - �����");
static std::string please_input("--> ");
static std::string differ("\t---\t---\t---");

static std::string main_menu("\t- ����� ������ N - ");
static std::string sub_menu("\t** ��������� ����� ����� ����� ����");

static std::string main_menu1("1 - ����� ����...");
static std::string main_menu2("2 - ���������� �������...");
static std::string main_menu3("3 - �������� �������");
static std::string main_menu4("4 - ������ ���� ���������");
static std::string main_menu5("5 - ���������� �������� ��������");
static std::string main_menu6("6 - ��������� ������ � ��������� �� �����");
static std::string main_menu7("7 - �������� ������ � ���������...");
static std::string main_menu8("8 - ����� ���������� ��������...");

static std::string sub_menu1("1 - �������� ������� ����������� ������");
static std::string sub_menu2("2 - ������� ������ �� ������� ������� �����");
static std::string sub_menu3("3 - ������������� ��������� ��������� ����������� �����������");
static std::string sub_menu0("0 - ����� ��� ���������");


