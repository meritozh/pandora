#ifndef PANDORA_SUPPORT_COMMANDLINE_H
#define PANDORA_SUPPORT_COMMANDLINE_H

#include <cassert>
#include <ostream>
#include <string>

namespace pandora {

namespace cl {

// Command line option processing entry point.
bool ParseCommandLineOptions(int argc,
                             const char *const *argv,
                             std::string Overview = "",
                             std::ostream *Errs = nullptr);

// Environment variable option processing alternative entry point.
void ParseEnvironmentOptions(const char *progName,
                             const char *envVar);

} /* cl */

} /* pandora */

#endif /* ifndef PANDORA_SUPPORT_COMMANDLINE_H */
