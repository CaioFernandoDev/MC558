#include <iostream>
#include <vector>

using namespace std;

void sort(vector<pair<int, int> > &v)
{
    for (unsigned int i = 0; i < v.size() - 1; i++)
    {
        for (unsigned int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j].second < v[j + 1].second)
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void sortVector(vector<int> &v)
{
    for (unsigned int i = 0; i < v.size() - 1; i++)
    {
        for (unsigned int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void sortMatrix(vector<pair<int, vector<int> > > &v)
{
    for (unsigned int i = 0; i < v.size() - 1; i++)
    {
        for (unsigned int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j].first > v[j + 1].first)
            {
                swap(v[j], v[j + 1]);
            }
        }
    }

    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (!v[i].second.empty())
        {
            sortVector(v[i].second);
        }
    }
}

int search(vector<pair<int, vector<int> > > &v, int elem)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i].first == elem)
        {
            return i;
        }
    }

    return -1;
}

vector<pair<int, vector<int> > > havelHakimiHelper(vector<pair<int, int> > &v)
{
    vector<pair<int, vector<int> > > output;
    vector<pair<int, vector<int> > > emptyOutput;
    vector<int> empVector;

    if (v.size() == 1)
    {
        if (v[0].second == 0)
        {
            output.push_back(pair<int, vector<int> >(v[0].first, empVector));
        }
        return output;
    }

    sort(v);

    if (v[0].second > int(v.size()) - 1)
    {
        return emptyOutput;
    }

    vector<pair<int, int> > newV;
    vector<int> indexes;
    for (int i = 1; i < int(v.size()); i++)
    {
        if (i <= v[0].second)
        {
            newV.push_back(pair<int, int>(v[i].first, v[i].second - 1));
            indexes.push_back(v[i].first);
        }
        else
        {
            newV.push_back(pair<int, int>(v[i].first, v[i].second));
        }
    }

    output = havelHakimiHelper(newV);

    if (output.empty())
    {
        return emptyOutput;
    }

    output.push_back(pair<int, vector<int> >(v[0].first, indexes));

    for (unsigned int i = 0; i < indexes.size(); i++)
    {
        output[search(output, indexes[i])].second.push_back(v[0].first);
    }

    return output;
}

vector<pair<int, vector<int> > > havelHakimi(vector<int> &v)
{
    vector<pair<int, int> > outputVector;

    for (unsigned int i = 0; i < v.size(); i++)
    {
        outputVector.push_back(pair<int, int>(i + 1, v[i]));
    }

    return havelHakimiHelper(outputVector);
}

int main()
{
    int n;
    cin >> n;

    vector<int> input(n);

    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    vector<pair<int, vector<int> > > output = havelHakimi(input);

    if (output.empty())
    {
        cout << "Não é sequência gráfica!" << endl;
        return 0;
    }

    sortMatrix(output);

    for (unsigned int i = 0; i < output.size(); i++)
    {
        for (unsigned int j = 0; j < output[i].second.size(); j++)
        {
            cout << output[i].second[j] << " ";
        }
        cout << endl;
    }

    return 0;
}