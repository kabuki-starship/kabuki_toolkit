/** Kabuki Theater - Cell Interactive Genetic Algorihm
    @version   0.x
    @file      /.../Source/Kabuki_Theater/Cell_IGA-Impl/GeneticPolygonTest.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2016 Cale McCollough <calemccollough.github.io>

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

#include <Kabuki_Theater/Cell_IGA/GeneticPolygonTest.h>

namespace Kabuki_Theater { namespace Cell_IGA {
    
GeneticPolygonTest::GeneticPolygonTest ()
{
    add (new GeneticPolygonTestPanel ());
}

static void main (String[] args)
{
    JFrame window = new JFrame ("GeneticPolygon Test App");
    window.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);

    window.setContentPane (new GeneticPolygonTestPanel ());
    
    window.pack ();
    window.setVisible (true);
}

}   //< namespace Kabuki_Theater { namespace Cell_IGA {
