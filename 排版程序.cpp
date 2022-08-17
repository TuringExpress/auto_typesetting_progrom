#include <bits/stdc++.h>
#include <windows.h>
#include <ctype.h>
#include <fstream>
using namespace std;
string name[12] = {"\0", "图灵编年史", "图灵恒枫谈", "图灵赐句", "图灵乐一乐", "图灵小橘灯", "图灵科普", "图灵挑战", "刷刷冷知识", "图灵秘史", "一言（ヒトコト）", "图灵航空"};//一言（ヒトコト） 
string fileName[12] = {"\0", "图灵编年史.txt", "图灵恒枫谈.txt", "图灵赐句.txt", "图灵乐一乐.txt", "图灵小橘灯.txt", "图灵科普.txt", "图灵挑战.txt", "刷刷冷知识.txt", "图灵秘史.txt", "一言（ヒトコト）.txt", "图灵航空.txt"};
string head[12] = {"\0", "|**<p class=\"ui tiny red label\">图灵编年史</p>**|", "|**<p class=\"ui tiny orange label\">图灵恒枫谈</p>**|", "|**<p class=\"ui tiny yellow label\">图灵赐句</p>**|", "|**<p class=\"ui tiny green label\">图灵乐一乐</p>**|", "|**<p class=\"ui tiny teal label\">图灵小橘灯</p>**|", "|**<p class=\"ui tiny olive label\">图灵科普</p>**|", "|**<p class=\"ui tiny blue label\">图灵挑战</p>**|", "|**<p class=\"ui tiny purple label\">刷刷冷知识</p>**|", "|**<p class=\"ui tiny pink label\">图灵秘史</p>**|", "|**<p class=\"ui tiny red label\">一言（ヒトコト）</p>**|", "|**<p class=\"ui tiny black label\">图灵航空</p>**|"};
string back = "\0";
string ntos(int t)
{
	int n = t;
	string ans = "\0";
	while(n)
	{
		int a = n % 10;
		ans += (char) ('0' + a);
		n /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
//非空行式正文,考虑空格,替换为"&nbsp;"(不包括双引号)
int main()
{
	cout << setlocale(LC_ALL, "chs_china.65001") << endl;
    //<开头>
    ifstream ifs;
    ofstream ofs;
    double qishu;//期数
    //获取期数
    ifs.open("期数储存.txt", ios::in);
    ifs >> qishu;
    ifs.close();
    ofs.open("最终文档.txt", ios::out);
    ofs << "### 图灵快报 第" << fixed << setprecision(1) << qishu << "期 ";
    //时间
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    char time[100] = {0};
    sprintf(time, "%4d年%02d月%02d日份", sys.wYear, sys.wMonth, sys.wDay);
    ofs << time << endl << endl;
    //图灵快报 版权所有
    ofs << "### [图灵快报](https://tm.turingicode.com/judge/article/1288) 版权所有" << endl;
    //</开头>
    //<内容>
    for(int i = 1;i <= 11;i++)
    {
    	int sw = 0, ss = 0, s_ = 0, sl = 0; //字数，句数，标点数，行数 
		string s;//读入用
        //将string型转为char[]型，否则ifs.open函数无法读取
        char fname[10] = {0};
        for(int j = 0;j <= fileName[i].length();j++)
        {
            fname[j] = fileName[i][j];
        }
        ifs.open(fname, ios::in);
        if(!ifs.good())
        {
        	cout << "文件无法读入" << endl;
			system("pause"); 
			return 1;
		}
        //标题
        ofs << "- - -" << endl;
        ofs << head[i] << endl;
        ofs << "|----------|" << endl;
        while(getline(ifs, s))
        {
        	ifs.clear();
        	ofs << "|";
            int len = s.length();
            for(int j = 0;j < len;j++)
            {
            	if(s[j] == ' ')
            	{
            		ofs << "&nbsp;";
				}
				else if(s[j] == '\t')
				{
					ofs << "&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else
				{
					ofs << s[j];
				}
				if(s[j] == '.' && s[j] == '。' && s[j] == '?' && s[j] == '!' && s[j - 1] == '？' && s[j] == '！' && s[j] == ';' && s[j] == '；')
				{
					s_++;
					if(s[j - 1] != '.' && s[j - 1] != '。' && s[j - 1] != '?' && s[j - 1] != '!' && s[j - 1] != '？' && s[j - 1] != '！' && s[j - 1] != ';' && s[j - 1] != '；')
					{
						ss++;
					}
				}
				else if(s[j] != ' ')
				{
					sw++;
				}
					
			}
			ofs << "|" << endl;
			sl++;
			if(sl != 0 || s[len - 2] != '.' && s[len - 2] != '。' && s[len - 2] != '?' && s[len - 2] != '!' && s[len - 2] != '？' && s[len - 2] != '！' && s[len - 2] != ';' && s[len - 2] != '；')
			{
				ss++;
			}
        }
        ifs.close();
		back += name[i] + ":\n";
		back += "字数:" + ntos(sw) + "\n";
		back += "句数:" + ntos(ss) + "\n";
		back += "标点数:" + ntos(s_) + "\n";
		back += "行数:" + ntos(sl) + "\n";
		back += "\n";
    }
    ofs << "- - -\n"; 
    //结尾
    ifs.open("结尾.txt", ios::in);
    ofs << "|**本期快报浏览人数**|\n";
    ofs << "|:-|\n"; 
    string s;
    while(getline(ifs, s))
    {
    	ofs << "|" << s << "|" << endl;
	}
	ofs.close();
	qishu += 0.1;
	ofs.open("期数储存.txt", ios::out);
	ofs << qishu;
	ofs.close();
	ofs.open("返回信息.txt", ios::out);
	ofs << back;
	ofs.close();
	system("pause"); 
    return 0;
}

