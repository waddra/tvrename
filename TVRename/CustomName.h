#pragma once

#include "Helpers.h"

using System::String;
using namespace System;

namespace TVRename
{
    ref class ProcessedEpisode;

    public ref class CustomName
    {
    public:
        String ^StyleString;

        static String ^DefaultStyle()
        {
            return Presets()[1];
        }

        static String ^OldNStyle(int n)
        {
            // enum class Style {Name_xxx_EpName = 0, Name_SxxEyy_EpName, xxx_EpName, SxxEyy_EpName, Eyy_EpName, 
	    // Exx_Show_Sxx_EpName, yy_EpName, NameSxxEyy_EpName, xXxx_EpName };

            // for now, this maps onto the presets
            if ((n >= 0) && (n < 9))
                return Presets()[n];
            else
                return DefaultStyle();
        }

        static StringList ^Presets()
        {
            StringList ^res = gcnew StringList();

            // if _any_ of these are changed, you'll need to change the OldNStyle function, too.
            res->Add("{ShowName} - {Season}x{Episode}[-{Season}x{Episode2}] - {EpisodeName}");
            res->Add("{ShowName} - S{Season:2}E{Episode}[-E{Episode2}] - {EpisodeName}");
            res->Add("{ShowName} S{Season:2}E{Episode}[-E{Episode2}] - {EpisodeName}");
            res->Add("{Season}{Episode}[-{Season}{Episode2}] - {EpisodeName}");
            res->Add("{Season}x{Episode}[-{Season}x{Episode2}] - {EpisodeName}");
            res->Add("S{Season:2}E{Episode}[-E{Episode2}] - {EpisodeName}");
            res->Add("E{Episode}[-E{Episode2}] - {EpisodeName}");
            res->Add("{Episode}[-{Episode2}] - {ShowName} - 3 - {EpisodeName}");
            res->Add("{Episode}[-{Episode2}] - {EpisodeName}");

            return res;
        }

        CustomName(int n) // old NStyle naming styles
        {
        }

        CustomName(CustomName ^O)
        {
            StyleString = O->StyleString;
        }

        CustomName(String ^s)
        {
            StyleString = s;
        }

        CustomName()
        {
            StyleString = DefaultStyle();
        }

        String ^NameFor(ProcessedEpisode ^pe)
        {
            return NameFor(pe, StyleString);
        }

        static StringList ^Tags();
        static String ^NameFor(ProcessedEpisode ^pe, String ^styleString);
    };


} // namespace
