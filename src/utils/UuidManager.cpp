#include "utils/UuidManager.hpp"

UUID::UUID() : id_counter(0)
{
    // uuid 관리자 생성
}


// uuid 발급
int UUID::issueID()
{
    boost::uuids::uuid uuid = generator();

    uuid_2_id.insert({uuid, id_counter});
    id_2_uuid.insert({id_counter, uuid});

    return id_counter++;
}

// uuid 삭제
void UUID::deleteID(int id)
{
    boost::uuids::uuid uuid;

    if(id_2_uuid.find(id) == id_2_uuid.end())
    {
        //에러 발생
        return;
    }

    uuid = id_2_uuid.at(id);

    id_2_uuid.erase(id);
    uuid_2_id.erase(uuid);

    return;
}