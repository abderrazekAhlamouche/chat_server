#include "message.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

std::string Message::iserialize()
{
std::ostringstream os;
boost::archive::text_oarchive archive(os);
archive << *this;
return  os.str();
}

void Message::ideSerialize(std::string& sMsg)
{
    std::istringstream is(sMsg);
    boost::archive::text_iarchive archive(is);
    archive >> *this ;


}