/** Kabuki Starship
    @file    /.../Source-Impl/_HMI/ParameterSet.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#include <_HMI/ParameterSet.h>

namespace _HMI {

inline size_type boundRange (size_type const value, size_type const min, size_type const max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

ParameterSet::ParameterSet (size_type newNumControls)
{
    newNumControls = boundRange (newNumControls, 0, ParameterSet::MaxNumElements);

    numParams = newNumControls;
    controls = new Parameter<T>*[newNumControls];

    for (size_type i = 0; i < newNumControls; ++i)
        controls[i] = nullptr;
}

ParameterSet::ParameterSet (const vector<Parameter<T>*>& newControls)
{
    size_type newNumControls = newControls.size ();

    if (newNumControls < MinNumElements)
    {
        // Copy what we can of the array and set the rest to nullptr.

        size_type i;
        for (i = 0; i < newNumControls; ++i)
            controls.push_back (newControls[i]);

        for (; i < MinNumElements; ++i)
            controls.push_back (nullptr);

        return;
    }

    for (size_type i = 0; i < newNumControls; ++i)
        controls[i] = newControls[i];
}

ParameterSet::ParameterSet (const ParameterSet& c)
{
    for (size_type i = 0; i < c.getNumParams (); ++i)
        controls.push_back (c.controls[i]);
}

ParameterSet::~ParameterSet ()
{
}

void ParameterSet::addControl (Parameter<T>& param)
{
    for (size_type i = 0; i < params.getNumParams (); ++i)
        newArray.push_back (controls[i]);
}

size_type ParameterSet::setParam (size_type index, Parameter<T>* c)
{
    if (index < 0) return -1;
    if (index > getCount ()) return 1;

    return 0;
}

size_type ParameterSet::setParam (size_type index, Parameter<T>& c)
{
    if (index < 0)
        return index;
    if (index >= getNumParams ())
        return index;

    controls[index] = c;
    return 0;
}

Parameter<T>* ParameterSet::removeControl (size_type index)
{
    if (index < 0)
        return nullptr;
    if (index >= getCount ())
        return nullptr;

    Parameter<T>* temp = controls[index];
    controls[index] = nullptr;
    return temp;
}

Parameter<T>* ParameterSet::getControl (size_type index)
{
    if (index < 0 || index >= getCount ())
        return nullptr;

    return controls[index];
}

size_type ParameterSet::getNumControls () const
{
    return numParams;
}

void ParameterSet::print () const
{
    _::printLine('~', Parameter<T>::MacroHeaderLength);
    std::cout << "Num Controls: " << getCount () << '\n';
    _::printLine('~', Parameter<T>::MacroHeaderLength);
    cout << Parameter<T>::MacroHeader << '\n';
    _::printLine ('~', Parameter<T>::MacroHeaderLength);

    printf ("numParams = %i", numParams);
    for (size_type i = 0; i < numParams; ++i)
    {
        auto currentControl = controls[i];

        if (currentControl == nullptr)
            printf("| nullptr  |      |      |      |     |     |       |    |        |      |\n");
        else
        {
            currentControl->printRow ();
            putchar ('\n');
        }
    }
    printf ("!!!!!!!!!!!!!!!!!!!");
    _::printLine ('~');
}

}   //< _HMI
