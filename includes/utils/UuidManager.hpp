#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <map>
#include <string>

class UUID
{
private:
    int id_counter;
    boost::uuids::random_generator generator;

    std::map<int, boost::uuids::uuid> id_2_uuid;
    std::map<boost::uuids::uuid, int> uuid_2_id;

public:
    UUID();

    int issueID();
    void deleteID(int idx);

};