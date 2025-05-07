#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int p = 31;
const int m = 2000;

struct Company
{
    string name, profit_tax, address;
};

struct HashTable
{
    vector <Company> table;
    vector <bool> exist;
};

vector <Company> readCompanyList(string file_name)
{
    ifstream is(file_name);
    vector <Company> result;
    Company temp;
    getline(is, temp.name); //bo qua dong dau tien
    if (!is)
    {
        cerr << "Cannot open information file!" << endl;
        return vector <Company> {};
    }
    while (getline(is, temp.name, '|'))
    {
        getline(is, temp.profit_tax, '|');
        getline(is, temp.address);
        result.push_back(temp);
    }
    is.close();
    return result;
}

long long hashString(string company_name)
{
    long long result = 0;
    int power = 1, j = 0;
    if (company_name.length() > 20) j = company_name.length() - 20; 
    for (; j < company_name.length(); ++j)
    {
        result = (result + company_name[j] * power) % m;
        power = (power * p) % m;
    }
    return result;
}

HashTable* createHashTable(vector <Company> list_company)
{
    HashTable* result = new HashTable;
    result->table.resize(2000);
    result->exist.resize(2000);
    int index, saved;
    for (int i = 0; i < list_company.size(); ++i)
    {
        index = saved = hashString(list_company[i].name);
        for (int j = 0; j < 2000; ++j)
        {
            index = (index + j) % 2000;
            if (!result->exist[index])
            {
                result->table[index] = list_company[i];
                result->exist[index] = true;
                break;
            }
        }
        if ((index + 1) % 2000 == saved % 2000) return result;
    }
    return result;
}

void insert(HashTable* hash_table, Company company)
{
    int index = hashString(company.name), table_length = hash_table->table.size();
    for (int i = 0; i < table_length; ++i)
    {
        index = (index + i) % table_length;
        if (!hash_table->exist[index])
        {
            hash_table->table[index] = company;
            hash_table->exist[index] = true;
            return;
        }
    }
}

Company* search(HashTable* hash_table, string company_name)
{
    int index = hashString(company_name), table_length = hash_table->table.size();
    for (int i = 0; i < table_length; ++i)
    {
        index = (index + i) % table_length;
        if (hash_table->exist[index] && hash_table->table[index].name == company_name)
        {
            return &hash_table->table[index];
        }
    }
    return nullptr;
}

int main(int N, char *A[])
{
    vector <Company> congty = readCompanyList(A[1]); 
    HashTable* list_company = createHashTable(congty);
    ifstream is(A[2]);
    ofstream os(A[3]);
    string info;
    Company* company = nullptr;
    if (!is)
    {
        cerr << "Cannot open input file!";
        return 1;
    }
    if (!os)
    {
        cerr << "Cannot open output file!";
        return 1;
    }
    while (getline(is, info))
    {
        company = search(list_company, info);
        if (company)
        {
            os << company->name << '|' << company->profit_tax << '|' << company->address << endl;
        }
        else
        {
            os << "Cannot find this company" << endl;
        }
    }
    is.close();
    os.close();
    return 0;
}