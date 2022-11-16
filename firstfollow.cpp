#include<bits/stdc++.h>
using namespace std;
int n;
char head[100];
string body[100], first[300] = {""};
set<char> follow[300];
bool visit[300] = {false};
bool check[300] = {false};
string table[100][300] = {""};

string terminal[] = { "id", "+", "*", "(", ")", "$" };

int indexNum(string s)
{
    for(int i=0; i<sizeof(terminal)/sizeof(terminal[0]); i++)
    {
        if(s==terminal[i])
            return i;
    }
    return -1;
}

bool isOperator(char c)
{
     if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='e' || c=='i')
        return true;
    return false;
}

void findFirst()
{
    for(int i=n-1; i>=0; i--)
    {
        if(body[i][0]=='i' && body[i][1]=='d')
        {
            first[head[i]]+='i';
            first[head[i]]+='d';
            if(first['i']=="")
                first['i']+="id";
        }
        else if(isOperator(body[i][0]))
        {
            first[head[i]]+=body[i][0];
            if(first[body[i][0]]=="")
                first[body[i][0]]+=body[i][0];
        }
        else
             first[head[i]]+=first[body[i][0]];
        first[head[i]]+=' ';
    }
    for(int i=0; i<n; i++)
        cout << "First(" << head[i] << ") = " << first[head[i]] << endl;
}

void findFollow()
{
    follow[head[0]].insert('$');
    int i, j, k, t;
    for(i=0; i<n; i++)
    {
        char c = head[i];
        if(!visit[c])
        {
           // cout << "c = " << c << endl;
            for(j=0; j<n; j++)
            {
                bool found = false;
                for(t=0; t<body[j].size(); t++)
                {
                    if(body[j][t]==c)
                    {
                        found=true;
                        break;
                    }
                }
                t++;
                while(found && t<body[j].size())
                {
                    char p = body[j][t];
                    if(isOperator(p))
                        follow[c].insert(p);
                    else
                    {
                        for(k=0; k<first[p].size(); k++)
                        {
                            if(first[p][k]!='e')
                                follow[c].insert(first[p][k]);
                        }
                    }
                    t++;
                }
                if(found && c!=head[j])
                    follow[c].insert(follow[head[j]].begin(), follow[head[j]].end());
            }
            cout << "Follow(" << c << ") = ";
        for(char ch: follow[c])
            cout << ch << " ";
        cout << endl;
        visit[c] = true;
        }

    }
}

void parseTable()
{
    int i, j, k = 0;
    for(i=0; i<n; i++)
    {
        char c = head[i];
        char p = body[i][0];
        if(p=='e')
        {
            cout << c << " " << body[i] << endl;
            for(auto ch: follow[c])
            {
                string s = "";
                s+=ch;
                int index = indexNum(s);
                //cout << "index = " << endl;
                if(index>=0)
                {
                    table[c][index]+=c;
                    table[c][index]+='->';
                    table[c][index]+=body[i];
                }
            }
        }
        else
        {
            for(j=0; j<first[p].size(); j++)
            {
                string s = "";
                if(first[p][j]!='e' && first[p][j]!=' ')
                {
                    if(first[p][j]=='i' && first[p][j+1]=='d')
                    {
                        //cout << "ID" << endl;
                        s = "id";
                        j++;
                    }
                    else
                        s+=first[p][j];
                    int index = indexNum(s);
                    if(index>=0)
                    {
                        table[c][index]+=c;
                        table[c][index]+="->";
                        table[c][index]+=body[i];
                    }

                }
            }
        }


    }
    cout << "PARSE TABLE" << endl;
    cout << "    ";
    for(int i=0; i<sizeof(terminal)/sizeof(terminal[0]); i++)
        cout << terminal[i] << "     ";
    cout << endl;
    k = 0;
    for(int i=0; i<n; i++)
    {
        char c = head[i];
        if(!check[c])
        {
            cout << c << "   ";
            for(j=0; j<sizeof(terminal)/sizeof(terminal[0]); j++)
                cout << table[c][j] << "    ";
            cout << endl;
            check[c] = true;
            //k++;
        }
    }

}

int main()
{
    freopen("emni_input.txt", "r", stdin);
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> head[i] >> body[i];
    freopen("emni_output.txt", "w", stdout);
    findFirst();
    findFollow();
    parseTable();
    return 0;
}
