/*
 * Name: main.cpp
 * Description: Driver simulator for page replacement policies
 * Author: devanshavasthi
 */

#include "policies.h"

int frames;
vector<int> pageSeq;
FILE *file;

void init(string name)
{

    fstream fout;
    fout.open(name, ios::out);
    fout << "frames"
         << ","
         << "hit-ratio" << endl;
    fout.close();
}

void init_all()
{

    fstream fout;
    fout.open("graph/all.csv", ios::out);
    fout << "frames"
         << ","
         << "hit-ratio"
         << ","
         << "policy" << endl;
    fout.close();
}

void get_data()
{

    file = fopen("pages.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    int page;
    while (fscanf(file, "%d", &page) != EOF)
        pageSeq.push_back(page);
    fclose(file);
}

void write_csv(string name, pair<int, float> temp)
{

    fstream fout;
    fout.open(name, ios::app);
    fout << temp.first << "," << temp.second << endl;
    fout.close();
}

void write_csv_all(string name, pair<int, float> temp, string policy)
{

    fstream fout;
    fout.open(name, ios::app);
    fout << temp.first << "," << temp.second << "," << policy << endl;
    fout.close();
}

void policy_menu()
{

    cout << endl;
    cout << "1. Random policy." << endl;
    cout << "2. Optimal policy." << endl;
    cout << "3. NRU policy." << endl;
    cout << "4. FIFO policy." << endl;
    cout << "5. FIFO with second chance policy." << endl;
    cout << "6. Clock policy." << endl;
    cout << "7. LRU policy." << endl;
    cout << "8. NFU policy." << endl;
    cout << "9. Working set policy." << endl;
    cout << "10. Aging policy." << endl;
    cout << "11. WSClock policy." << endl;
    cout << "Please select any one policy to continue: ";
    int choice;
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
    {
        init("graph/random.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = randomReplacement(frames, pageSeq, 1);
            write_csv("graph/random.csv", temp);
        }
        string x = "python3 graph/print_random.py";
        system(x.c_str());
        x = "xdg-open graph/random.png";
        system(x.c_str());
        break;
    }
    case 2:
    {
        init("graph/optimal.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = optimalReplacement(frames, pageSeq, 1);
            write_csv("graph/optimal.csv", temp);
        }
        string x = "python3 graph/print_optimal.py";
        system(x.c_str());
        x = "xdg-open graph/optimal.png";
        system(x.c_str());
        break;
    }
    case 3:
    {
        init("graph/nru.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = nru(frames, pageSeq, 1);
            write_csv("graph/nru.csv", temp);
        }
        string x = "python3 graph/print_nru.py";
        system(x.c_str());
        x = "xdg-open graph/nru.png";
        system(x.c_str());
        break;
    }
    case 4:
    {
        init("graph/fifo.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = fifoPagereplacement(frames, pageSeq, 1);
            write_csv("graph/fifo.csv", temp);
        }
        string x = "python3 graph/print_fifo.py";
        system(x.c_str());
        x = "xdg-open graph/fifo.png";
        system(x.c_str());
        break;
    }
    case 5:
    {
        init("graph/fifo2.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = FIFO2Replacement(frames, pageSeq, 1);
            write_csv("graph/fifo2.csv", temp);
        }
        string x = "python3 graph/print_fifo2.py";
        system(x.c_str());
        x = "xdg-open graph/fifo2.png";
        system(x.c_str());
        break;
    }
    case 6:
    {
        init("graph/clock.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = clockReplacement(frames, pageSeq, 1);
            write_csv("graph/clock.csv", temp);
        }
        string x = "python3 graph/print_clock.py";
        system(x.c_str());
        x = "xdg-open graph/clock.png";
        system(x.c_str());
        break;
    }
    case 7:
    {
        init("graph/lru.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = lru(pageSeq, frames, 1);
            write_csv("graph/lru.csv", temp);
        }
        string x = "python3 graph/print_lru.py";
        system(x.c_str());
        x = "xdg-open graph/lru.png";
        system(x.c_str());
        break;
    }
    case 8:
    {
        init("graph/nfu.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = nfuPageReplacement(frames, pageSeq, 1);
            write_csv("graph/nfu.csv", temp);
        }
        string x = "python3 graph/print_nfu.py";
        system(x.c_str());
        x = "xdg-open graph/nfu.png";
        system(x.c_str());
        break;
    }
    case 9:
    {
        init("graph/workingset.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = workingset(pageSeq, frames, 1);
            write_csv("graph/workingset.csv", temp);
        }
        string x = "python3 graph/print_workingset.py";
        system(x.c_str());
        x = "xdg-open graph/workingset.png";
        system(x.c_str());
        break;
    }
    case 10:
    {
        init("graph/aging.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = aging(frames, pageSeq, 1);
            write_csv("graph/aging.csv", temp);
        }
        string x = "python3 graph/print_aging.py";
        system(x.c_str());
        x = "xdg-open graph/aging.png";
        system(x.c_str());
        break;
    }
    case 11:
    {
        init("graph/wsclock.csv");
        while (true)
        {
            cout << "Please enter the number of frames: ";
            cin >> frames;
            if (!frames)
                break;
            pair<int, float> temp = wsclock(frames, pageSeq, 1);
            write_csv("graph/wsclock.csv", temp);
        }
        string x = "python3 graph/print_wsclock.py";
        system(x.c_str());
        x = "xdg-open graph/wsclock.png";
        system(x.c_str());
        break;
    }
    default:
        cout << "Please select valid option" << endl;
        break;
    }
}

void run_all()
{

    pair<int, float> temp;
    while (true)
    {
        cout << "Please enter the number of frames: ";
        cin >> frames;
        if (!frames)
            break;
        temp = randomReplacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "random");

        temp = optimalReplacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "optimal");

        temp = nru(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "nru");

        temp = fifoPagereplacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "fifo");

        temp = FIFO2Replacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "fifo2");

        temp = clockReplacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "clock");

        temp = lru(pageSeq, frames, 0);
        write_csv_all("graph/all.csv", temp, "lru");

        temp = nfuPageReplacement(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "nfu");

        temp = workingset(pageSeq, frames, 0);
        write_csv_all("graph/all.csv", temp, "workingset");

        temp = aging(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "aging");

        temp = wsclock(frames, pageSeq, 0);
        write_csv_all("graph/all.csv", temp, "wsclock");
    }
    string x = "python3 graph/print_all.py";
    system(x.c_str());
    x = "xdg-open graph/policy.png";
    system(x.c_str());
}

int main()
{

    // Main menu of the simulator
    while (true)
    {
        cout << endl;
        cout << "WELCOME TO PAGE REPLACEMENT SIMULATOR" << endl;
        cout << "1. Simulate single policy." << endl;
        cout << "2. Simulate all policies." << endl;
        cout << "3. Exit." << endl;
        int choice;
        cout << "Please select any one option to continue: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            get_data();
            policy_menu();
            break;
        case 2:
            get_data();
            init_all();
            run_all();
            break;
        case 3:
            cout << "Thank you" << endl;
            exit(0);
        default:
            cout << "Please select valid option" << endl;
            break;
        }
    }
    return 0;
}