#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "strings_algorithms.h"

using namespace std;

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9B%D0%B0%D0%BD%D0%B4%D0%B0%D1%83-%D0%92%D0%B8%D1%88%D0%BA%D0%B8%D0%BD%D0%B0_(k_%D1%80%D0%B0%D0%B7%D0%BB%D0%B8%D1%87%D0%B8%D0%B9)

int main()
{
    string x("father");
    string y(R"(In entirely be to at settling felicity. Fruit two match men you seven share. Needed as or is enough points. Miles at smart ﻿no marry whole linen mr. Income joy nor can wisdom summer. Extremely depending he gentleman improving intention rapturous as.

        Bed sincerity yet therefore forfeited his certainty neglected questions.Pursuit chamber as elderly amongst on.Distant however warrant farther to of.My justice wishing prudent waiting in be.Comparison age not pianoforte increasing delightful now.Insipidity sufficient dispatched any reasonably led ask.Announcing if attachment resolution sentiments admiration me on diminution.)");

    auto res = string_algorithms::task2_k_differences(y, x, 2);

    cout << x << "\n" << y << "\n\n";
    for (auto index : res)
    {
        cout << index << "\n";
    }
}