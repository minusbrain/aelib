/**
 * @author     Andreas Evers <aevers@gmx.de>
 *
 * @copyright  Copyright © 2020 Andreas Evers <aevers@gmx.de>
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

namespace base
{
/**
 * \brief Conditionally transform each element of an input range to an output container
 *
 * This algorithm transforms each element of an input range matching a provided predicate
 * into a new container using the provided transformation function.
 *
 * Consider the following code snippet
 * \code
 * auto transIntHalf = [](int in) -> int { return (int)(in / 2); };
 * auto predIfEven = [](int in) -> bool { return (in % 2) == 0; };
 *
 *  std::vector<int> vecIn{1, 4, 3, 2, 1, 8, 2, 1};
 *  std::vector<int> vecOut{};
 *
 *  base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
 *                     transIntHalf, predIfEven);
 * \endcode
 * vecOut now contains {2, 1, 4, 1} half of every even integer in the original
 * vector
 *
 * \param[in]     first      Iterator indicating the beginning of the range to transform
 *                           from
 * \param[in]     last       Iterator indicating the end of the range to transform
 *                           from
 * \param[in,out] out        Writeable Iterator to the container to insert the
 *                           transformed items into
 * \param[in]     transFunc  Transformation function to transform each matching item from
 *                           the input range to the output iterator
 * \param[in]     predFunc   Predicate function to check every element in the input range
 *                           against
 * \return    'out' Iterator - pointing one after the last transformed element in the out
 *            container
 */
template <class InIter, class OutIter, class Trans, class Pred>
inline OutIter transform_if(InIter first, InIter last, OutIter out, Trans transFunc,
                            Pred predFunc)
{
    for (; first != last; ++first)
    {
        if (predFunc(*first))
        {
            *out = transFunc(*first);
        }
    }
    return (out);
}
}  // namespace base
