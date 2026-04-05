/*
 * Message_Folder.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "Message_Folder.h"

#include <iostream>

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void swap(Folder &lhs, Folder &rhs)
{
    using std::swap;
    for (auto m : lhs.messages)
        m->remFldr(&lhs);
    for (auto m : rhs.messages)
        m->remFldr(&rhs);

    swap(lhs.messages, rhs.messages);

    for (auto m : lhs.messages)
        m->addFldr(&lhs);
    for (auto m : rhs.messages)
        m->addFldr(&rhs);
}
void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}
void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}
void Message::add_to_folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}
void Message::remove_from_folders()
{
    for (auto f : folders)
        f->remMsg(this);
    folders.clear();
}
Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_folders(m);
}
Message::~Message()
{
    remove_from_folders();
}
Message &Message::operator=(const Message &rhs)
{
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}
void Folder::add_to_messages(const Folder &f)
{
    for (auto m : f.messages)
        m->addFldr(this);
}
Folder::Folder(const Folder &f) : messages(f.messages)
{
   add_to_messages(f);
}
void Folder::remove_from_messages()
{
    for (auto m : messages)
        m->remFldr(this);
    messages.clear();
}
Folder::~Folder()
{
    remove_from_messages();
}
Folder &Folder::operator=(const Folder &rhs)
{
    remove_from_messages();
    messages = rhs.messages;
    add_to_messages(rhs);
    return *this;
}

void Message::printtxt()
{
   std::cout << "contents: " << contents << std::endl;
}

void Message::printfolders()
{
   std::string str("************************");
   std::cout << str << std::endl;
   std::cout << "All folders messages: " << std::endl;
   for (auto f : folders)
   {
      f->printmsg();
   }
}

void Folder::printmsg()
{
   std::cout << "Msg: " << std::endl;
   for (auto m : messages)
      std::cout << m->contents << std::endl;
}

int main()
{
   Message me("Hello world!");
   Folder* tags = new Folder();
   me.save(*tags);
   me.printtxt();
   me.printfolders();
   tags->printmsg();
   return 0;
}
