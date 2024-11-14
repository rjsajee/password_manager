#ifndef PROFILE_MODEL_H
#define PROFILE_MODEL_H

#include <string>
#include <map>  // std::map and std::multimap

enum class AppType { Website, DesktopApplication, Game };

struct PasswordRecord {
    int id;
    AppType appType;
    std::string creatorUsername;
    std::string appUsername;
    std::string password;
    std::string appName;
    std::string extraInfo;
    std::string dateCreated;
    std::string dateLastUpdated;
};

class ProfileModel {
public:
    ProfileModel(const std::string& username);

    bool addPassword(const PasswordRecord& record);
    bool editPassword(int id, const PasswordRecord& updatedRecord);
    bool deletePassword(int id);
    std::map<int, PasswordRecord> getAllPasswords() const;
    std::map<int, PasswordRecord> getUserPasswords() const;
    std::multimap<std::string, PasswordRecord> getPasswordsByLastUpdatedDate(const std::string& date) const;

    std::string getUsername() const;
    static std::string getCurrentDate();
    std::string generateRandomPassword(int length = 12);
    std::string hashPassword(const std::string& password);

    static std::string appTypeToString(AppType type);
    static AppType stringToAppType(const std::string& typeStr);

private:
    std::string username;
    std::map<int, PasswordRecord> passwords;
    int nextId;

    void loadPasswords();
    void savePasswords() const;
};

#endif
