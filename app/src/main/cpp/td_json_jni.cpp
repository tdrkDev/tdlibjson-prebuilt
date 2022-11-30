//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2020
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <td/telegram/td_json_client.h>

#define EXPORT __attribute__ ((visibility ("default")))

extern "C" {

EXPORT void *td_json_client_create() {
  return new td::ClientJson();
}

EXPORT void td_json_client_destroy(void *client) {
  delete static_cast<td::ClientJson *>(client);
}

EXPORT void td_json_client_send(void *client, const char *request) {
  static_cast<td::ClientJson *>(client)->send(td::Slice(request == nullptr ? "" : request));
}

EXPORT const char *td_json_client_receive(void *client, double timeout) {
  return static_cast<td::ClientJson *>(client)->receive(timeout);
}

EXPORT const char *td_json_client_execute(void *client, const char *request) {
  return td::ClientJson::execute(td::Slice(request == nullptr ? "" : request));
}

EXPORT int td_create_client_id() {
  return td::json_create_client_id();
}

EXPORT void td_send(int client_id, const char *request) {
  td::json_send(client_id, td::Slice(request == nullptr ? "" : request));
}

EXPORT const char *td_receive(double timeout) {
  return td::json_receive(timeout);
}

EXPORT const char *td_execute(const char *request) {
  return td::json_execute(td::Slice(request == nullptr ? "" : request));
}

EXPORT void td_set_log_message_callback(int max_verbosity_level, td_log_message_callback_ptr callback) {
  td::ClientManager::set_log_message_callback(max_verbosity_level, callback);
}
}
