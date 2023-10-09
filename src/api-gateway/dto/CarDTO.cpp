#include "CarDTO.h"

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

#include <exceptions/server_exceptions.h>

void CarDTO::FromJSON(const std::string &json)
{
    Json::Value value;
    Json::Reader reader;

    if (!reader.parse(json, value))
    {
        throw JsonParserException("can't parse PersonDTO object");
    }

    id = value["id"].asUInt64();
    carUid = value["car_uid"].asString();
    brand = value["brand"].asString();
    model = value["model"].asString();
    registrationNumber = value["registration_number"].asString();
    power = value["power"].asUInt64();
    price = value["price"].asUInt64();
    type = value["type"].asString();
    availability = value["availability"].asBool();
}

Json::Value GetJSON(const CarDTO &person)
{
    Json::Value root;

    root["id"] = (uint)person.id;
    root["car_uid"] = person.carUid;
    root["brand"] = person.brand;
    root["model"] = person.model;
    root["registration_number"] = person.registrationNumber;
    root["power"] = (uint)person.power;
    root["price"] = (uint)person.price;
    root["type"] = person.type;
    root["availability"] = person.availability;

    return root;
}

std::string CarDTO::ToJSON() const
{
    Json::Value root = GetJSON(*this);

    Json::FastWriter writer;

    return writer.write(root);
}

std::string ToJSON(const CarsDTO &cars)
{
    Json::Value arr = Json::arrayValue;

    for (auto car : cars)
    {
        Json::Value root = GetJSON(car);
        arr.append(root);
    }

    Json::FastWriter writer;

    return writer.write(arr);
}

std::string ToJSON(const CarsDTO &cars, size_t page, size_t pageSize)
{
    Json::Value root;

    root["page"] = page;
    root["pageSize"] = pageSize;
    root["totalElements"] = cars.size();

    Json::Value items = Json::arrayValue;
    for (auto car : cars)
    {
        Json::Value val = GetJSON(car);
        items.append(val);
    }

    root["items"] = items;

    Json::FastWriter writer;
    return writer.write(root);
}
