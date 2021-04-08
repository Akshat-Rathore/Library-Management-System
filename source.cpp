#include <iostream>
#include <vector>
#include <string.h>
#include <dirent.h>
#include <fstream>
#include <map>
#include <set>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;

void show_guidelines(int arg = 0)
{
    if (arg)
        cout << "<----------Welcome to the Library Management System---------->\n\n\nPlease follow the following guidelines to continue....\n";
    else
        cout << "<------------------------Guidelines------------------------>\n";
    cout << endl;
    cout << "Enter 0 to get the list of all the books along with their filename, title, and author name:\n";
    cout << "Enter 1 to search for a book and read or analyze it:\n";
    cout << "Enter 2 to get the guidelines list again:\n";
    cout << "Enter -1 to quit:\n";
    cout << endl;
    cout << "<-------------------------------------------------------------->\n\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "No directory provided!Exiting.....\n";
        exit(-1);
    }

    DIR *dir;
    struct dirent *diread;

    if ((dir = opendir(argv[1])) != nullptr)
    {

        map<string, string> index;
        set<string> current;
        string index_path = string(argv[1]) + "\\index.txt";

        ifstream fin(index_path);

        if (fin)
        {
            string line;
            if (fin)
            {
                while (fin)
                {
                    getline(fin, line);
                    if (line.find("Novel") != std::string::npos)
                    {
                        int pos = line.find("Novel");
                        index[line.substr(0, --pos)] = "Novel";
                    }
                    else if (line.find("Play") != std::string::npos)
                    {
                        int pos = line.find("Play");
                        index[line.substr(0, --pos)] = "Play";
                    }
                }
            }
            fin.close();
        }

        bool new_books = true;

        while ((diread = readdir(dir)) != nullptr)
        {
            if ((diread->d_name)[0] != '.')
            {
                string file_name = diread->d_name;
                int n = file_name.length();
                string ext = file_name.substr(n - 3);

                if (n > 4 && ext == "txt")
                {
                    string filepath = string(argv[1]) + "\\" + diread->d_name;
                    ifstream fp(filepath);

                    if (fp)
                    {
                        string line;

                        while (fp)
                        {
                            getline(fp, line);
                            if (line.length() && line.find("Title: ") != std::string::npos)
                            {
                                string title = line.substr(7, line.length() - 7);
                                if (index.find(title) == index.end())
                                {
                                    if (new_books)
                                    {
                                        cout << "New books are detected!Please enter required details:\n";
                                        new_books = false;
                                    }
                                    cout << "Enter the type of the book " << title << ":";
                                    string type;
                                    cin >> type;
                                    index[title] = type;
                                }

                                current.insert(title);
                                break;
                            }
                        }
                    }
                    fp.close();
                }
            }
        }

        closedir(dir);

        ofstream f_index(index_path);

        if (f_index)
        {
            for (auto itr = index.begin(); itr != index.end();)
            {
                if (current.count(itr->first))
                {
                    f_index << itr->first << ' ' << itr->second << '\n';
                    itr++;
                }
                else
                    itr = index.erase(itr);
            }
            f_index.close();
        }
        else
        {
            cout << "Index.txt couldn't be created!Exiting...";
            exit(-1);
        }

        current.clear();

        show_guidelines(1);
        string sch[10][3];
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 3; j++)
                sch[i][j] = "";
        int bn = 0;
        int uy = 0;
        while (true)
        {
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            while (getchar() != '\n')
                ;

            if (choice == 0)
            {


                    DIR *dir1;
                    struct dirent *diread1;
                    if ((dir1 = opendir(argv[1])) != nullptr)
                    {
                        string index_path1 = string(argv[1]) + "\\index.txt";

                        string name, auth_name, type;
                        string srch[10][3];
                        int it = 0;

                        while ((diread = readdir(dir1)) != nullptr)
                        {
                            if ((diread->d_name)[0] != '.')
                            {
                                string file_name = diread->d_name;
                                int n = file_name.length();
                                string ext = file_name.substr(n - 3);

                                if (n > 4 && ext == "txt")
                                {

                                    string filepath = string(argv[1]) + "\\" + diread->d_name;
                                    ifstream fp2(filepath);
                                    if (fp2)
                                    {
                                        string line2;
                                        while (fp2)
                                        {
                                            getline(fp2, line2);
                                            string line_3 = line2;

                                            if (line2.length() && line2.find("Author: ") != std::string::npos)
                                            {
                                                auth_name = line2.substr(8, line2.length() - 8);
                                            }
                                            if (line_3.length() && line_3.find("Title: ") != std::string::npos)
                                            {
                                                name = line_3.substr(7, line_3.length() - 7);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        cout << "Cant't access files!!";
                                    }
                                    fp2.close();
                                    int chck = 1;
                                    for (int i = 0; i < 10; i++)
                                        if (sch[i][0] == file_name)
                                            chck = 0;
                                    if (chck)
                                    {
                                        sch[bn][0] = srch[it][0] = file_name;
                                        sch[bn][1] = srch[it][1] = name;
                                        sch[bn][2] = srch[it][2] = auth_name;
                                    }

                                    for (int i = 1; i < 3; i++)
                                    {
                                        transform(sch[bn][i].begin(), sch[bn][i].end(), sch[bn][i].begin(), ::toupper);
                                    }
                                    if (uy == 0)
                                    {

                                        it++;
                                        bn++;
                                    }

                                    if (file_name != "index.txt")
                                    {

                                        cout << "\nFile Name: " << file_name << "\n"
                                             << "Title: " << name << "\n"
                                             << "Author: " << auth_name << "\n"
                                             << endl;
                                    }
                                }
                            }
                        }
                    }
                    closedir(dir1);
                }
                else if (choice == 1)
                {
                    cout << "\nEnter 1 to search by title and 2 to search by author:";
                    int c = 0;
                    cin >> c;
                    int fla = 1;
                    while (getchar() != '\n')
                        ;
                    if (c == 1)
                    {
                        cout << "\nEnter the title of the book:";
                        string gt;
                        getline(cin, gt);

                        transform(gt.begin(), gt.end(), gt.begin(), ::toupper);
                        int flag = 0;
                        for (int i = 1; i <= bn; i++)
                        {
                            if (gt == sch[i][1])
                            {
                                if (flag == 0)
                                {
                                    cout << "\nBook Found!" << endl;
                                    flag++;
                                }
                                cout << "\nFile Name: " << sch[i][0] << "  Title: " << sch[i][1] << "  Author: " << sch[i][2] << "\n"
                                     << endl;
                            }
                        }
                        if (flag == 0)
                        {

                            cout << "\nSorry, no book with title " << gt << " exists in the library.Please check if the spelling is correct!" << endl;
                        }
                    }
                    else if (c == 2)
                    {
                        cout << "\nEnter the author of the book:";
                        string gt;
                        getline(cin, gt);
                        transform(gt.begin(), gt.end(), gt.begin(), ::toupper);
                        int flag = 0;
                        for (int i = 0; i < bn; i++)
                        {
                            if (gt == sch[i][2])
                            {
                                if (flag == 0)
                                    cout << "\nBooks Found!" << endl;
                                cout << "\nFile Name: " << sch[i][0] << "  Title: " << sch[i][1] << "  Author: " << sch[i][2] << "\n"
                                     << endl;
                                flag++;
                            }
                        }
                        if (flag == 0)
                        {
                            cout << "Sorry, no book with author " << gt << " exists in the library.Please check if the spelling is correct!\n";
                        }
                    }
                    else
                    {
                        cout << "wrong choice";
                        fla = 0;
                    }
                    if (fla != 0)
                    {
                        cout << "\nEnter 1 to display a book of your choice and perform some analysis in it!" << endl;
                        cout << "Enter 0 to see the guidelines. " << endl;
                        int c = 0;
                        cin >> c;
                        while (getchar() != '\n')
                            ;
                        if (c == 1)
                        {
                            cout << "Enter the title of the book you want to read : ";
                            string n;
                            getline(cin, n);
                            transform(n.begin(), n.end(), n.begin(), ::toupper);
                            string file_name, title, type;
                            int flag3 = 0;
                            for (int i = 0; i < 3; i++)
                            {
                                if (n == sch[i][1])
                                {
                                    file_name = sch[i][0];
                                    title = sch[i][1];
                                    flag3 = 1;
                                    cout << "Match Found" << endl;
                                    break;
                                }
                            }
                            if (flag3 == 1)
                            {
                                DIR *dir2;
                                int ch = 0;
                                struct dirent *diread2;
                                if ((dir2 = opendir(argv[1])) != nullptr)
                                {
                                    while ((diread2 = readdir(dir2)) != nullptr)
                                    {
                                        if ((diread2->d_name)[0] != '.')
                                        {
                                            string file_name4 = diread2->d_name;
                                            int n = file_name4.length();
                                            string ext = file_name4.substr(n - 3);

                                            if (n > 4 && ext == "txt")
                                            {
                                                string filepath1 = string(argv[1]) + "\\" + diread2->d_name;
                                                if (file_name == file_name4)
                                                {
                                                    ch++;
                                                    ifstream fp4(filepath1);
                                                    if (fp4)
                                                    {
                                                        string line4;
                                                        int counter = 0;

                                                        while (fp4)
                                                        {
                                                            getline(fp4, line4);

                                                            const char d[4] = " ";
                                                            char *tok;
                                                            int l = line4.length();
                                                            char char4[l + 1];
                                                            strcpy(char4, line4.c_str());
                                                            tok = strtok(char4, d);
                                                            cout << line4 << endl;
                                                            while (tok != 0)
                                                            {
                                                                counter++;
                                                                tok = strtok(0, d);
                                                            }
                                                            if (counter >= 1000)
                                                            {
                                                                cout << "[Number of words printed: " << counter << " ]" << endl;
                                                                cout << "Enter 1 to get the next 1000 words and 0 to stop reading: ";
                                                                int in = 0;
                                                                cin >> in;
                                                                if (in == 1)
                                                                {
                                                                    counter = 0;
                                                                }
                                                                else
                                                                {
                                                                    break;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << "Couldn't openn the required file   :( ";
                                                    }

                                                    fp4.close();
                                                    int jh = 0;
                                                    string index_path1 = string(argv[1]) + "\\index.txt";

                                                    ifstream fin1(index_path1);
                                                    if (fin1)
                                                    {

                                                        string line5;
                                                        while (fin1)
                                                        {

                                                            getline(fin1, line5);
                                                            transform(line5.begin(), line5.end(), line5.begin(), ::toupper);

                                                            if (line5.find(title) != std::string::npos)
                                                            {

                                                                string lne = line5;
                                                                std::size_t found = lne.find_last_of(" ");

                                                                type = lne.substr(found + 1);

                                                                break;
                                                            }
                                                        }
                                                    }
                                                    fin1.close();

                                                    if (type == "NOVEL")
                                                    {
                                                        cout << "Enter a word whose maximum frequency areas are to be found: ";
                                                        string word = "";
                                                        cin >> word;
                                                        cout << "Enter 1 to get the Chapters with maximum frequencies and 0 to get the Paragraphs :" << endl;
                                                        int cho = 0;
                                                        cin >> cho;

                                                        if (cho == 0)
                                                        {
                                                            string file_path = string(argv[1]) + "\\" + file_name;
                                                            vector<int> par;
                                                            vector<int> cnt;
                                                            ifstream fp6(file_path);
                                                            if (fp6) //To calculate the frequency in each paragraph
                                                            {
                                                                string s6;
                                                                int ct = 0, ln = 0, lnl = 0, flag = 0;
                                                                while (fp6)
                                                                {
                                                                    ln++;
                                                                    getline(fp6, s6);
                                                                    if (s6 == "") // If the paragraph ends, start the counter again and store line no.
                                                                    {
                                                                        if (flag == 0)
                                                                            par.push_back(1);
                                                                        else
                                                                            par.push_back(lnl);
                                                                        flag++;
                                                                        cnt.push_back(ct);
                                                                        ct = 0;
                                                                        lnl = ln + 1;
                                                                    }
                                                                    const char d[6] = " ,.!?";
                                                                    char *tok;
                                                                    int l = s6.length();
                                                                    int lw = word.length();
                                                                    char char4[l + 1];
                                                                    strcpy(char4, s6.c_str());
                                                                    tok = strtok(char4, d);
                                                                    while (tok != 0)
                                                                    {
                                                                        string s(tok);
                                                                        if (!s.compare(word))
                                                                            ct++;
                                                                        tok = strtok(0, d);
                                                                    }
                                                                }
                                                            }
                                                            fp6.close();

                                                            for (int i = 0; i < par.size(); i++) //Sorting the vectors
                                                            {
                                                                for (int j = 1; j < par.size(); j++)
                                                                {
                                                                    if (cnt[i] > cnt[j])
                                                                    {
                                                                        cnt[i] = cnt[i] + cnt[j];
                                                                        cnt[j] = cnt[i] - cnt[j];
                                                                        cnt[i] = cnt[i] - cnt[j];
                                                                        par[i] = par[i] + par[j];
                                                                        par[j] = par[i] - par[j];
                                                                        par[i] = par[i] - par[j];
                                                                    }
                                                                }
                                                            }
                                                            ifstream fp7(file_path);
                                                            if (fp7)
                                                            {
                                                                string s7;
                                                                int line = 0, npr = 0, flg = 0;

                                                                while (fp7)
                                                                {
                                                                    if (npr > 4)
                                                                        break;
                                                                    getline(fp7, s7);

                                                                    line++;

                                                                    if (line == par[npr])
                                                                        flg = 1;
                                                                    if (flg)
                                                                    {
                                                                        cout << s7 << endl;
                                                                    }
                                                                    if (s7 == "" && flg == 1)
                                                                    {
                                                                        cout << "\n";
                                                                        if (npr < 4)
                                                                            cout << "(word \"" << word << "\"  in paragraph : " << cnt[npr + 1] << " )\n"
                                                                                 << endl;
                                                                        npr++;
                                                                        flg = 0;
                                                                        line = 0;
                                                                        fp7.clear();
                                                                        fp7.seekg(0);
                                                                    }
                                                                }
                                                            }
                                                            fp7.close();
                                                        }
                                                        else if (cho == 1)
                                                        {
                                                            string file_path7 = string(argv[1]) + "\\" + file_name;
                                                            ifstream fp6(file_path7);
                                                            int ln = 0, cnt = 0;
                                                            int ch[200][3];
                                                            int f = 0;
                                                            if (fp6)
                                                            {
                                                                string s6;
                                                                for (int i = 0; i < 200; i++)
                                                                {
                                                                    for (int j = 0; j < 3; j++)
                                                                        ch[i][j] = 0;
                                                                }
                                                                while (fp6)
                                                                {

                                                                    ln++;
                                                                    getline(fp6, s6);
                                                                    string sc = s6;

                                                                    const char d[6] = " ,.!?";
                                                                    char *tok;
                                                                    int l = s6.length();
                                                                    char char4[l + 1];
                                                                    strcpy(char4, s6.c_str());
                                                                    tok = strtok(char4, d);
                                                                    while (tok != 0)
                                                                    {
                                                                        string s(tok);
                                                                        if (s == word)
                                                                            cnt++;
                                                                        tok = strtok(0, d);
                                                                    }
                                                                    s6 = sc;

                                                                    if (s6.find("CHAPTER") != std::string::npos)
                                                                    {
                                                                        f++;

                                                                        if (f == 1)
                                                                            ch[f - 1][2] = 0;
                                                                        else
                                                                            ch[f - 1][2] = cnt;
                                                                        cnt = 0;

                                                                        ch[f][0] = ln;
                                                                        ch[f - 1][1] = ln - 1;
                                                                    }
                                                                }
                                                            }
                                                            fp6.close();

                                                            for (int i = 0; i < 199; i++) //Sorting according to frequency of word
                                                            {
                                                                for (int j = 0; j < 199 - i; j++)
                                                                {
                                                                    if (ch[i][2] > ch[j][2])
                                                                    {
                                                                        int cht[3];
                                                                        for (int k = 0; k < 3; k++)
                                                                        {
                                                                            cht[k] = ch[i][k];
                                                                        }
                                                                        for (int k = 0; k < 3; k++)
                                                                        {
                                                                            ch[i][k] = ch[j][k];
                                                                        }
                                                                        for (int k = 0; k < 3; k++)
                                                                        {
                                                                            ch[j][k] = cht[k];
                                                                        }
                                                                    }
                                                                }
                                                            }

                                                            ifstream fp7(file_path7);
                                                            if (fp7)
                                                            {
                                                                string s7;
                                                                int line = 0, ncr = 0, flg = 0;

                                                                while (fp7)
                                                                {
                                                                    line++;
                                                                    if (ncr > 4)
                                                                        break;
                                                                    getline(fp7, s7);

                                                                    if (line < ch[ncr][1] && line >= ch[ncr][0])
                                                                    {
                                                                        if (flg == 0)
                                                                        {
                                                                            cout << (ncr + 1) << "."
                                                                                 << "( Chapter with word count for \"" << word << "\"  :" << (ch[ncr][2] + 1) << " )\n\n"
                                                                                 << endl;
                                                                        }
                                                                        flg++;
                                                                        cout << s7 << endl;
                                                                    }
                                                                    else if (line == ch[ncr][1])
                                                                    {
                                                                        ncr++;
                                                                        flg = 0;
                                                                        line = 0;
                                                                        fp7.clear();
                                                                        fp7.seekg(0);
                                                                    }
                                                                    else
                                                                    {
                                                                        continue;
                                                                    }
                                                                }
                                                            }
                                                            fp7.close();
                                                        }
                                                    }

                                                    else if (type == "PLAY")
                                                    {

                                                        cout << "Enter the name of a character of your choice:";
                                                        string chrt;
                                                        while (getchar() != '\n')
                                                            ;
                                                        getline(cin, chrt);
                                                        transform(chrt.begin(), chrt.end(), chrt.begin(), ::toupper);
                                                        string file_path = string(argv[1]) + "\\" + file_name;
                                                        ifstream f6(file_path);
                                                        int f = 0, l1 = 0, l2 = 0, line = 0, fl = 0;
                                                        if (f6)
                                                        {
                                                            string s6;

                                                            while (f6)
                                                            {
                                                                getline(f6, s6);
                                                                line++;

                                                                if (s6.find("SCENE") != std::string::npos)
                                                                {
                                                                    f++;
                                                                    if (f % 2 == 0)
                                                                    {
                                                                        l2 = line;
                                                                    }
                                                                    else
                                                                    {
                                                                        l1 = line;
                                                                    }
                                                                    if (fl != 0 && f >= 2)
                                                                    {
                                                                        break;
                                                                    }
                                                                }
                                                                if (s6.find(chrt) != std::string::npos)
                                                                {
                                                                    fl = 1;
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            cout << "Can't open the book!" << endl;
                                                        }
                                                        f6.close();
                                                        if (l1 > l2)
                                                        {
                                                            l1 = l1 + l2;
                                                            l2 = l1 - l2;
                                                            l1 = l1 - l2;
                                                        }
                                                        ifstream fp7(file_path);
                                                        line = 0;
                                                        f = fl = 0;
                                                        vector<string> list;
                                                        if (fp7)
                                                        {
                                                            string s7;
                                                            while (fp7)
                                                            {
                                                                getline(fp7, s7);
                                                                line++;
                                                                if (line < l1)
                                                                    continue;
                                                                else if (line >= l2)
                                                                    break;
                                                                const char d[6] = " .";
                                                                char *tok;
                                                                int l = s7.length();
                                                                int ct = 0;
                                                                char char4[l + 1];
                                                                strcpy(char4, s7.c_str());
                                                                tok = strtok(char4, d);
                                                                while (tok != 0)
                                                                {
                                                                    ct++;
                                                                    tok = strtok(0, d);
                                                                }
                                                                if (ct == 1)
                                                                {
                                                                    list.push_back(s7);
                                                                }
                                                            }
                                                        }
                                                        fp7.close();
                                                        vector<string>::iterator ip;

                                                        std::sort(list.begin(), list.end());
                                                        list.erase(std::unique(list.begin(), list.end()), list.end());

                                                        cout << "Characters with " << chrt << " in a scene are as follows:" << endl;
                                                        vector<string>::iterator ptr;
                                                        for (ptr = list.begin(); ptr < list.end(); ptr++)
                                                        {
                                                            if (*ptr != "No." && *ptr != "Out.")
                                                                cout << *ptr << " ";
                                                        }
                                                        cout << endl;
                                                    }
                                                }
                                                else
                                                {
                                                    continue;
                                                }
                                            }
                                        }
                                    }
                                    if (ch == 0)
                                    {
                                        cout << "Could not find the book you are looking for :(";
                                    }
                                }
                                else
                                {
                                    cout << "Could not open the directory!";
                                }
                                closedir(dir2);
                            }
                            else
                            {
                                cout << "Couldn't match any book with it! Please check the name entered.Thank you." << endl;
                            }
                        }
                        else
                        {
                            show_guidelines();
                        }
                    }
                }
                else if (choice == 2)
                {
                    show_guidelines();
                }
                else if (choice == -1)
                {
                    cout << "Thank you for visiting!\n";
                    break;
                }
                else
                {
                    cout << "Invalid input!Please follow the guidelines!...\n";
                }
                uy++;
            }
        }
        else
        {
            perror("opendir");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
