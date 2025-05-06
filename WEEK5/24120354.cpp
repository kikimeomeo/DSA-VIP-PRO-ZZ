#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
string hople = "+-*/() 1234567890"; //cac ki tu hop le trong mot bieu thuc phep tinhtinh
string notanumber = "+-*/() "; //khong phai so
string congtru = "+-"; 
string nhanchia = "*/";
int diff_so_toantu = 0; //chenh lech giua so va toan tu
int diff_ngoac = 0; //chech lech giua ( và )

//khai bao ham
int max(int a, int b);
void swap(string &a, string &b);
void reverseString(string &a);
int dot_index(string a);
string deletedot(string a);
void chuanhoa(string &a);
void lamtron2chuso(string &a);
queue <string> operation(string line);
string bigintSum(string a, string b);
string bigSum(string a, string b);
string bigintSub(string a, string b);
string bigSub(string a, string b);
string smallMul(string a, char b);
string bigintMul(string a, string b);
string bigMul(string a, string b);
char smallDiv(string a, string b);
string bigintDiv(string a, string b);
string bigDiv(string a, string b);
string calculate(queue <string> operation);

//viet ham
int max(int a, int b) //tim so lon hon
{
    return (a < b) ? b : a;
}

void swap(string &a, string &b) //doi gia tri
{
    string temp = a;
    a = b;
    b = temp;
}

void reverseString(string &a) //dao nguoc chuoi lai
{
    for (int i = 0; i < a.length() / 2; ++i)
    {
        char temp = a[i];
        a[i] = a[a.length() - 1 - i];
        a[a.length() - 1 - i] = temp;
    }
}

int dot_index(string a) //vi tri cua dau cham
{
    for (int i = 0; i < a.length(); ++i)
    {
        if (a[i] == '.') return i;
    }
    return a.length() - 1;
}

string deletedot(string a) //xoa dau cham
{
    for (int i = 0; i < a.length(); ++i)
    {
        if (a[i] == '.') return a.substr(0, i) + a.substr(i + 1);
    }
    return a;
}

void chuanhoa(string &a) //chuan hoa so ve dung dang, lay 100 so sau dau . de ket qua chinh xac cao hon, xoa cac so 0 du thua
{
    int i = 0;
    bool am = false;
    if (a[0] == '-') 
    {
        ++i;
        am = true;
    }
    if (a.length() - dot_index(a) - 1 > 100) a = a.substr(0, dot_index(a) + 100 + 1); //
    if (a.find('.') != string::npos)
    {
        while (a[i] == '0' && a[i + 1] != '.') ++i;
        int j = a.length() - 1;
        while (a[j] == '0' && a[j - 1] != '.') --j;
        if (a[j] == '0') a = a.substr(i, j - i + 1 - 2);
        else if (a[j] == '.') a = a.substr(i, j - i + 1 - 1);
        else a = a.substr(i, j - i + 1);
    }
    else
    {
        while (a[i] == '0' && i < a.length() - 1) ++i;
        a = a.substr(i);
    }
    if (am) a = '-' + a;
}

void lamtron2chuso(string &a) //ham lam tron den 2 chu so thap phan
{
    int am = 0;
    if (a[0] == '-') 
    {
        am = 1;
    }
    a = a.substr(am, a.length() - am);
    a = deletedot(a);
    int i = a.length() - 1;
    while (i >= 0 && a[i] == '9') a[i--] = '0';
    if (i < 0)
    {
        a = '1' + a;
    }
    else
    {
        ++a[i];
    }
    a.insert(a.end() - 2, '.');
    if (am == 1) a = '-' + a;
}

queue <string> operation(string line) //tu line, tao ra queue chua so va thu tu phep tinh 
{
    if (line.length() == 0) return queue <string> {}; //khong co gi thi tra ve queue rong
    bool check[256]{}; //mang check xem co phan tu nao cua b khong nam trong a khong
    for (int i = 0; i < hople.length(); ++i) check[(int)hople[i]] = true;
    for (int i = 0; i < line.length(); ++i) if (!check[(int)line[i]]) return queue <string> {}; //neu phan tu o b khong thuoc a thi tra ve queue rong
    stack <string> operators; //chua toan tu va dau ngoac
    queue <string> temp_operation; //chua so, va toan tu khi can thiet
    int i = 0;
    while (i < line.length())
    {
        string temp;
        if (line[i] == ' ') //neu la dau cach thi bo qua
        {
            ++i;
            continue;
        }
        if (notanumber.find(line[i]) == string::npos) //neu la so thi chay while de lay het so do
        {
            while (i < line.length() && notanumber.find(line[i]) == string::npos) 
            {
                temp += line[i++];
            }
        }
        else temp = line[i++]; //la ki tu thi lay ki tu
        if (notanumber.find(temp[0]) == string::npos) //neu la so thi cho vao queue va tang bien diff_so_toantu
        {
            temp_operation.push(temp);
            ++diff_so_toantu;
        }
        else //khong phai so thi xet cac truong hop
        {
            if (temp == ")") //la dau ) thi lan luot bo cac phan tu dau cua stack vao queue cho toi khi gap dau ( sau do giam bien diff_ngoac
            {
                --diff_ngoac;
                if (diff_so_toantu == 0 || diff_ngoac < 0) return queue <string> {}; //neu co toan tu hoac ko co ca so va toan tu truoc dau ) thi tra ve queue rong, neu ) dang nhieu hon ( thi bieu thuc ko hop le, tra ve queue rong
                while (!operators.empty() && operators.top() != "(")
                {
                    temp_operation.push(operators.top());
                    operators.pop();
                }
                operators.pop();
            }
            else if (temp == "-" && notanumber.find(line[i]) == string::npos) //gap dau -, kiem tra xem no co dinh lien voi so ko, neu co thi do la so am, lay so am roi cho vao queue, tang bien diff_so_toantu
            {
                while (i < line.length() && notanumber.find(line[i]) == string::npos) 
                {
                    temp += line[i++];
                }
                temp_operation.push(temp);
                ++diff_so_toantu;
            }
            else if (!operators.empty() && temp != "(" && (nhanchia.find(operators.top()) != string::npos || (congtru.find(temp) != string::npos && congtru.find(operators.top()) != string::npos)))
            //neu stack khong rong, va phan tu tren cung ko phai (, thi thuc hien kiem tra neu temp la toan tu co do uu tien <= top cua stack thi day top cua stack vao queue, sau do xoa top, va them temp vao stack
            {
                while ((!operators.empty() && (nhanchia.find(operators.top()) != string::npos || (congtru.find(temp) != string::npos && congtru.find(operators.top()) != string::npos))))
                {
                    temp_operation.push(operators.top());
                    operators.pop();
                }
                operators.push(temp);
                --diff_so_toantu;
            }
            else
            {
                operators.push(temp); //day temp vao stack
                if (temp != "(") //neu temp khong phai dau ( thi nghia la temp la toan tu +-*/, khi do giam bien diff_so_toantu
                {
                    --diff_so_toantu;
                }
                else //neu temp la ( thi ta kiem tra tiep
                {
                    while (i < line.length() && line[i] == ' ') ++i;
                    if (i == line.length() || line[i] == ')') return queue <string> {}; //neu phan tu tiep theo (line[i]) la ) nghia la no tao ra (), ko hop le nen tra ve queue rong
                    ++diff_ngoac; //tang bien diff_ngoac
                }
            }
        }
        //1 so phai toi 1 toan tu +-*/, nen neu chenh lech > 1 hoac < 0 thi nghia la bieu thuc sai dinh dang, tra ve queue rong
        if (diff_so_toantu < 0 || diff_so_toantu > 1) return queue <string> {};
    }
    //cuoi cung thi so phai nhieu hon toan tu +-*/ 1 don vi, nen neu khac 1 thi sai dinh dang, tra ve queue rong
    //diff_ngoac != 0 thi co nghia so dau ( khac so dau ) nen sai dinh dang, tra ve queue rong
    if (diff_so_toantu != 1 || diff_ngoac != 0) return queue <string> {};
    while (!operators.empty()) //day het nhung gi con lai trong stack vao queue
    {
        temp_operation.push(operators.top());
        operators.pop();
    }
    return temp_operation;
}

string bigintSum(string a, string b) //ham tinh tong 2 so nguyen duong
{
    string result;
    if (a.length() < b.length()) swap(a, b);
    int moduls = 0, diff = a.length() - b.length();
    for (int i = b.length() - 1; i >= 0; --i) //dung so co do dai ngan hon lam moc
    {
        result += static_cast <char> ((a[i + diff] + b[i] - 2 * '0' + moduls) % 10 + '0');
        moduls = (a[i + diff] + b[i] - 2 * '0' + moduls) / 10; //phan du
    }
    if (moduls == 0) //khong du
    {
        for (int i = diff - 1; i >= 0; --i) //them vao result cac chu so con lai
        {
            result += a[i];
        }
    }
    else //du 1
    {
        for (int i = diff - 1; i >= 0; --i)
        {
            result += static_cast <char> ((a[i] - '0' + moduls) % 10 + '0');
            moduls = (a[i] - '0' + moduls) / 10;
        }
        if (moduls == 1) 
        {
            result += '1'; //den cuoi cung van du 1 thi them so 1 vao cuoi 
        }
    }
    reverseString(result); //dao nguoc lai chuoi de co ket qua
    return result;
}

string bigSum(string a, string b) //ham tinh tong 2 so duong
{
    string result;
    int dota_length = a.length() - dot_index(a) - 1, dotb_length = b.length() - dot_index(b) - 1; //so chu so thap phan
    //xoa dau cham cua a va b
    a = deletedot(a);
    b = deletedot(b);
    //them so 0 vao cho bang nhau ve so chu so thap phan
    if (dota_length < dotb_length) 
    {
        a += string(dotb_length - dota_length, '0');
    }
    else
    {
        b += string(dota_length - dotb_length, '0');
    }
    //chuan hoa a, b tranh nhieu so 0 thua, gay tinh lau hon
    chuanhoa(a);
    chuanhoa(b);
    result = bigintSum(a, b); //cong hai so nguyen
    result.insert(result.end() - max(dota_length, dotb_length), '.'); //them dau cham, vi tri se la cua so co so chu so thap phan lon hon
    chuanhoa(result); //chuan hoa
    return result;
}

string bigintSub(string a, string b) //ham tinh hieu 2 so nguyen duong
{
    bool am = false; //kiem tra ket qua co am khong
    string result;
    if (a.length() < b.length() || (a.length() == b.length() && a < b))
    {
        swap(a, b); //cho a la so lon hon de tinh
        am = true;
    }
    int moduls = 0, diff = a.length() - b.length();
    for (int i = b.length() - 1; i >= 0; --i)
    {
        //be hon 0 thi nho mot, nghia la moduls = 1, nguoc lai moduls = 0
        if (a[i + diff] - b[i] - moduls < 0)
        {
            result += static_cast <char> (a[i + diff] - b[i] - moduls + 10 + '0');
            moduls = 1;
        }
        else
        {
            result += static_cast <char> (a[i + diff] - b[i] - moduls + '0');
            moduls = 0;
        }
    }
    if (diff > 0) //chenh lech do dai > 0 thi thuc hien
    {
        if (moduls == 0)
        {
            for (int i = diff - 1; i >= 0; --i)
            {
                result += a[i]; //them vao result cac chu so con lai
            }
        } // 2090 - 4
        else
        {
            for (int i = diff - 1; i >= 0; --i)
            {
                if (a[i] - moduls < '0') //nghia la phai nho 1, a[i] = '0', la thanh 10 - 1 = 9
                {
                    result += '9';
                }
                else
                {
                    result += static_cast <char> (a[i] - moduls); //them cac chu so con lai
                    moduls = 0;
                }
            }
        }
    }
    reverseString(result); //dao nguoc chuoi
    chuanhoa(result); //chuan hoa
    if (am) result = '-' + result; //neu am them dau -
    return result;
}

string bigSub(string a, string b) //ham tinh hieu 2 so duong
{
    //tuong tu phep cong hai so duong
    string result;
    int dota_length = a.length() - dot_index(a) - 1, dotb_length = b.length() - dot_index(b) - 1;
    a = deletedot(a);
    b = deletedot(b);
    if (dota_length < dotb_length) 
    {
        a += string(dotb_length - dota_length, '0');
    }
    else
    {
        b += string(dota_length - dotb_length, '0');
    }
    //chuan hoa a, b tranh nhieu so 0 thua, gay tinh lau hon
    chuanhoa(a);
    chuanhoa(b);
    result = bigintSub(a, b);
    result.insert(result.end() - max(dota_length, dotb_length), '.');
    chuanhoa(result);
    return result;
}

string smallMul(string a, char b) //ham tinh tich 1 so nguyen duong va 1 so nguyen duong nho
{
    string result;
    if (a == "0" || b == '0') return "0"; //1 trong hai so la 0 thi tra ve 0 luon
    int moduls = 0;
    for (int i = a.length() - 1; i >= 0; --i)
    {
        result += static_cast <char> (((a[i] - '0') * (b - '0') + moduls) % 10 + '0'); //phan don vi sau moi lan nhan
        moduls = ((a[i] - '0') * (b - '0') + moduls) / 10; //phan du sau moi lan nhan
    }
    if (moduls != 0) result += static_cast <char> (moduls + '0'); //neu con du, thi them phan du do vao result
    reverseString(result); //dao nguoc de ra ket qua
    chuanhoa(result); //chuan hoa
    return result;
}

string bigintMul(string a, string b) //ham tinh tich 2 so nguyen duong
{
    string result = "0";
    if (a.length() < b.length()) swap(a, b); //cho a la so co do dai lon hon
    int addZero = 0; //so chu so 0 them vao sau moi lan nhan, vi du lan 1 la hang don vi, lan 2 la hang chuc,.....
    for (int i = b.length() - 1; i >= 0; --i) 
    {
        result = bigSum((smallMul(a, b[i]) + string(addZero++, '0')), result); //cong don result, result = result + (tich cua a va b[i] + addZero so 0 dang sau tich)
    }
    chuanhoa(result); //chuan hoa
    return result;
}

string bigMul(string a, string b) //ham tinh tich 2 so duong
{
    string result;
    if (a == "1") return b; //neu 1 trong 2 so = 1 thi tra ve so con lai
    if (b == "1") return a;
    if (a == "0" || b == "0") return "0"; //neu 1 trong 2 so = 0 thi tra ve 0
    //phan duoi tuong tu phep cong hai so duong
    int dota_length = a.length() - dot_index(a) - 1, dotb_length = b.length() - dot_index(b) - 1;
    a = deletedot(a);
    b = deletedot(b);
    if (dota_length < dotb_length)
    {
        a += string(dotb_length - dota_length, '0');
    }
    else
    {
        b += string(dota_length - dotb_length, '0');
    }
    //chuan hoa a, b tranh nhieu so 0 thua, gay tinh lau hon
    chuanhoa(a);
    chuanhoa(b);
    result = bigintMul(a, b);
    //neu 2 * so chu so thap phan lon hon trong hai so >= do dai ket qua hien tai, thi phai them cho du so 0 vao truoc ket qua hien tai de them duoc dau . dung vi tri
    if (2 * max(dota_length, dotb_length) >= result.length())
    {
        result = string(2 * max(dota_length, dotb_length) - result.length() + 1, '0') + result; // them 2 * max(dota_length, dotb_length) - result.length() + 1 vao truoc ket qua
    }
    result.insert(result.end() - 2 * max(dota_length, dotb_length), '.'); //dat dau . dung vi tri
    chuanhoa(result); //chuan hoa
    return result;
}

char smallDiv(string a, string b) //ham tinh thuong cua so nguyen duong a so voi so nguyen duong nho b
{
    //bien dem i se cham hon 1 don vi do voi temp, nghia la ban dau i = 0, temp = b * 1
    char i = '0';
    string temp = b;
    while (temp.length() < a.length() || (temp.length() == a.length() && temp <= a)) //chay den khi nao temp > a thi ngung, sau do tra ve i
    {
        ++i;
        temp = bigintSum(temp, b);
    }
    return i;
}

string bigintDiv(string a, string b) //ham tinh thuong so nguyen duong a so voi so nguyen duong b
{
    string result, temp = "0";
    string moduls = "0";
    a = a + string(100, '0'); //them 100 so 0 vao sau a de cho so duoc tinh chi tiet
    for (int i = 0; i < a.length(); ++i) //chay het so a, gan temp 
    {
        if (temp.length() < b.length() || (temp.length() == b.length() && temp < b))  //neu khong chia duoc cho b thi tiep tuc them a[i] vao temp
        {
            temp += a[i];
        }
        else //neu chia duoc thi temp = phan du
        {
            moduls = bigintSub(temp, smallMul(b, smallDiv(temp, b))); //phan du = temp - b * phan nguyen
            temp = moduls + a[i];
        }
        chuanhoa(temp); //chuan hoa temp tranh viec temp co so 0 dang truoc, gay loi
        result += smallDiv(temp, b); //them vao ket qua phan nguyen cua phep chia
    }
    return result;
}

string bigDiv(string a, string b) //ham tinh thuong so duong a so voi so duong b
{
    string result;
    if (b == "1") return a; //neu b = 1 thi tra ve a
    if (a == "0") return "0"; //neu a = 0 thi tra ve 0
    //tuong tu phep cong
    int dota_length = a.length() - dot_index(a) - 1, dotb_length = b.length() - dot_index(b) - 1;
    a = deletedot(a);
    b = deletedot(b);
    if (dota_length < dotb_length)
    {
        a += string(dotb_length - dota_length, '0');
    }
    else
    {
        b += string(dota_length - dotb_length, '0');
    }
    //chuan hoa a, b tranh viec a, b co thua so 0 dang truoc, gay loi
    chuanhoa(a);
    chuanhoa(b);
    result = bigintDiv(a, b); 
    result.insert(result.end() - 100, '.'); //them dau . vao truoc 100 so
    chuanhoa(result); //chuan hoa
    return result;
}

string calculate(queue <string> operations) //ham tinh ket qua cua bieu thuc toan hoc
{
    if (operations.empty()) return "Error: Malformed expression detected."; //queue rong => bieu thuc khong hop le
    stack <string> temp_operation; //stack chua so de thuc hien cac phep tinh
    string num1, num2, result; //bien luu so va ket qua
    while (!operations.empty())
    {
        if (notanumber.find(operations.front()) == string::npos) //neu la so thi them vao stack
        {
            temp_operation.push(operations.front());
        }
        else //neu khong phai so thi thuc hien
        {
            num2 = temp_operation.top(); //so thu hai
            temp_operation.pop();
            num1 = temp_operation.top(); //so dau
            temp_operation.pop();
            if (operations.front() == "+") //truong hop cong
            {
                if (num1[0] == '-' && num2[0] == '-')
                {
                    temp_operation.push("-" + bigSum(num1.substr(1), num2.substr(1)));
                }
                else if (num1[0] == '-')
                {
                    temp_operation.push(bigSub(num2, num1.substr(1)));
                }
                else if (num2[0] == '-')
                {
                    temp_operation.push(bigSub(num1, num2.substr(1)));
                }
                else
                {
                    temp_operation.push(bigSum(num1, num2));
                }
            }
            else if (operations.front() == "-") //truong hop tru
            {
                if (num1[0] == '-' && num2[0] == '-')
                {
                    temp_operation.push(bigSub(num2.substr(1), num1.substr(1)));
                }
                else if (num1[0] == '-')
                {
                    temp_operation.push("-" + bigSum(num1.substr(1), num2));
                }
                else if (num2[0] == '-')
                {
                    temp_operation.push(bigSum(num1, num2.substr(1)));
                }
                else
                {
                    temp_operation.push(bigSub(num1, num2));
                }
            }
            else if (operations.front() == "*") //truong hop nhan
            {
                if (num1[0] == '-' && num2[0] == '-')
                {
                    temp_operation.push(bigMul(num1.substr(1), num2.substr(1)));
                }
                else if (num1[0] == '-')
                {
                    temp_operation.push("-" + bigMul(num1.substr(1), num2));
                }
                else if (num2[0] == '-')
                {
                    temp_operation.push("-" + bigMul(num1, num2.substr(1)));
                }
                else
                {
                    temp_operation.push(bigMul(num1, num2));
                }                
            }
            else //truong hop chia
            {
                if (num2 == "0") //so thu hai, la so chia, neu = 0 nghia la khong tinh duoc, loi
                {
                    return "Error: Division by zero is not allowed.";
                }
                if (num1[0] == '-' && num2[0] == '-')
                {
                    temp_operation.push(bigDiv(num1.substr(1), num2.substr(1)));
                }
                else if (num1[0] == '-')
                {
                    temp_operation.push("-" + bigDiv(num1.substr(1), num2));
                }
                else if (num2[0] == '-')
                {
                    temp_operation.push("-" + bigDiv(num1, num2.substr(1)));
                }
                else
                {
                    temp_operation.push(bigDiv(num1, num2));
                }      
            }
        }
        operations.pop(); //loai bo phan tu vua trong queue vua duoc cho vao stack
    }
    //chuan hoa ket qua ve 2 chu so thap phan, dong thoi lam tron
    if (temp_operation.top().length() - 1 - dot_index(temp_operation.top()) > 2) 
    {
        result = temp_operation.top().substr(0, dot_index(temp_operation.top()) + 1 + 2);
        if (temp_operation.top()[dot_index(temp_operation.top()) + 1 + 2] >= '2') 
        {
            lamtron2chuso(result);
        }
    }
    else
    {
        result = temp_operation.top();
    }
    chuanhoa(result); //chuan hoa ket qua lan cuoi, tranh du thua so 0
    if (result == "-0") 
    {
        result = "0"; //tranh truong hop "-0"
    }
    return result;
}

int main(int N, char *A[])
{
    ifstream is(A[1]); //file input
    ofstream os(A[2]); //file output
    if (!is)
    {
        cerr << "cannot open input file!";
        return 1;
    }
    if (!os)
    {
        cerr << "cannot open output file!";
        return 1;
    }
    string line; //chua tung dong trong file input
    queue <string> operations; //luu ket qua queue co duoc tu line
    string result; //ket qua sau khi tinh
    while (getline(is, line)) //doc moi dong trong file input vao line den khi het file
    {
        operations = operation(line); //goi ham ket qua queue
        result = calculate(operations); //goi ham tinh ket qua bieu thuc
        os << result << endl; //in ra file output
        diff_ngoac = diff_so_toantu = 0; //sau moi lan tinh, reset lai hai bien diff
    }
    //dong file
    is.close();
    os.close();
    return 0;
}