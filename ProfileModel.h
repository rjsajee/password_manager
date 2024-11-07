#ifndef PROFILE_MODEL_H
#define PROFILE_MODEL_H

#include <string>
#include <vector>

enum class AppType { Website, DesktopApplication, Game };

struct PasswordRecord {
    int id;
    AppType appType;
    std::string username;
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
    std::vector<PasswordRecord> getAllPasswords() const;
    std::vector<PasswordRecord> getUserPasswords() const;  // New function for user-specific passwords

    std::string getUsername() const;
    static std::string getCurrentDate();

private:
    std::string username;
    std::vector<PasswordRecord> passwords;
    int nextId;

    void loadPasswords();
    void savePasswords() const;
};

#endif
