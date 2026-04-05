/*
 * Message_Folder.h
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MESSAGE_FOLDER_H
#define MESSAGE_FOLDER_H
#include <string>
#include <set>

class Folder;
class Message
{
    friend void swap(Message &, Message &);
    friend void swap(Folder &, Folder &);
    friend class Folder;
public:
    explicit Message(const std::string str = "") : contents(str) {}
    Message(const Message&);
    Message & operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
    void printtxt();
    void printfolders();
private:
    std::string contents;
    std::set<Folder *> folders;

    void add_to_folders(const Message&);
    void remove_from_folders();

    void addFldr(Folder *f) {folders.insert(f);}
    void remFldr(Folder *f) {folders.erase(f);}
};

void swap(Message &, Message &);
void swap(Folder &, Folder &);

class Folder
{
    friend void swap(Message &, Message &);
    friend void swap(Folder &, Folder &);
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder&);
    Folder & operator=(const Folder&);
    ~Folder();
    void printmsg();

private:
    std::set<Message *> messages;

    void add_to_messages(const Folder&);
    void remove_from_messages();

    void addMsg(Message *m) {messages.insert(m);}
    void remMsg(Message *m) {messages.erase(m);}
};

#endif /* !MESSAGE_FOLDER_H */
