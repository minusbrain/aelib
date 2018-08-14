#pragma once

namespace ae
{
    /**

    */
    template<class InIter, class OutIter, class Trans, class Pred>
    OutIter transform_if(InIter begin, InIter end, OutIter out, Trans transFunc, Pred predFunc)
    {
        for (; begin != end; ++begin, ++out) {
            if (predFunc(*begin)) {
                *out = transFunc(*begin);
            }
        }
        return (out);
    }
}
