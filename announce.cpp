#include "announce.h"
#include <iostream>
#include "optionmanager.h"
#include "urioptionreader.h"

Announce::Announce(const std::string& uri)
{
    std::istringstream stream(uri);
    OptionManager options(new UriOptionReader(stream));
    options.addOption("info_hash", infohash)
    .addOption("peer_id", peerid)
    .addOption("port", port)
    .addOption("uploaded", uploaded)
    .addOption("downloaded", downloaded)
    .addOption("left", left)
    .addOption("compact", compact, true)
    .addOption("event", event, Announce::none)
    .addOption("numwant", numwant, 0);
    options.readOptions();
}

template <>
void from_string<Announce::Event>(Announce::Event& value, const std::string& str)
{
    if (str.empty())
        value = Announce::none;
    else if (str == "started")
        value = Announce::started;
    else if (str == "stopped")
        value = Announce::stopped;
    else if (str == "completed")
        value = Announce::completed;
    else
        value = Announce::invalid;
}
