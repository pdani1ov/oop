#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const std::string ERROR_MSG_DICTIONARY_FILE = "Dictionary file is not entered";
const std::string ERROR_MSG_ANY_LANGUAGES = "� ����� ������������ ��������� ������";
const std::string MSG_SAVE_CHANGES = "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.";
const std::string MSG_GOOD_BYE = "��������� ���������. �� ��������.";

bool ParseDictionary(std::multimap<std::string, std::string>& dictionary);
bool TranslateWords(std::multimap<std::string, std::string>& dictionary);