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

template <> void OptionImpl<Announce::Event>::setValue(const std::string& str)
{
    if (str == "started")
        m_value = Announce::started;
    else if (str == "stopped")
        m_value = Announce::stopped;
    else if (str == "completed")
        m_value = Announce::completed;
    else
        m_value = Announce::invalid;
}
