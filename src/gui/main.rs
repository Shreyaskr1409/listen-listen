use iced::{
    Element, Theme, widget::{button, column, text}
};

#[derive(Debug, Default)]
pub struct AppState {}

#[derive(Debug, Clone)]
pub enum Message {
    Exit,
}

pub fn new_app_state() -> AppState {
    AppState {}
}

pub fn view(_app_state: &AppState) -> Element<'_, Message> {
    column![
        text("Hello World!").size(20),
        button(text("Tap here")).on_press(Message::Exit),
    ].into()
}

pub fn update(_app_state: &mut AppState, message: Message) {
    match message {
        Message::Exit => println!("exit trigger")
    }
}

pub fn theme(_app_state: &AppState) -> Theme {
    Theme::KanagawaDragon
}

fn main() -> iced::Result {
    iced::application(new_app_state, update, view)
        .theme(theme)
        .run()
}
