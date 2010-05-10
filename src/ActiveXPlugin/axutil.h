/**********************************************************\ 
Original Author: Georg Fritzsche

Created:    Sept 17, 2009
License:    Dual license model; choose one of two:
            Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#include "Win/win_common.h"

class FbPerUserRegistration
{
public:
    FbPerUserRegistration(bool perUser = true);
    ~FbPerUserRegistration();

private:
#if _MSC_VER < 1500
    HKEY m_hkey;
#endif
};