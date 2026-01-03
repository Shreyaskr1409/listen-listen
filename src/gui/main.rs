mod component;
mod font;

use iced::{
    Alignment, Element, Font,
    Length::{self, Fill},
    Task, Theme,
    widget::{Space, button, column, container, row, rule, space::horizontal, text},
};

use crate::font::setup_fonts;

#[derive(Debug, Default)]
pub struct AppState {}

#[derive(Debug, Clone)]
pub enum Message {
    Default,
    Minimize,
    Maximize,
    Exit,
}

pub fn new_app_state() -> AppState {
    AppState {}
}

pub fn view(app_state: &AppState) -> Element<'_, Message> {
    column![app_state.header(), app_state.content(), app_state.footer()]
        .spacing(4)
        .padding(4)
        .into()
}

impl AppState {
    fn header(&self) -> Element<'_, Message> {
        container(
            column![
                row![
                    button("Home").on_press(Message::Default),
                    text("Listen-Listen").size(24),
                    horizontal(),
                    button("-").on_press(Message::Minimize),
                    button("=").on_press(Message::Maximize),
                    button("X").on_press(Message::Exit),
                ]
                .spacing(4),
                rule::horizontal(1),
                row![
                    container(Space::new().height(150).width(150)).style(container::rounded_box),
                    column![
                        column![
                            text("Postpostpartum").size(16),
                            text("Injury Reserve").size(12),
                            text("By the Time I Get to Phoenix").size(12),
                        ]
                        .spacing(4),
                        Space::new().height(Length::Fill),
                        row![
                            component::button::custom_buttom("\u{23EE}", 25.0, 25.0, 20.0),
                            component::button::custom_buttom("\u{25B6}", 25.0, 25.0, 16.0),
                            component::button::custom_buttom("\u{23ED}", 25.0, 25.0, 20.0),
                        ]
                        .spacing(4)
                    ]
                    .spacing(4)
                ]
                .spacing(8)
                .align_y(Alignment::Center)
                    .height(Length::Shrink),
            ]
            .spacing(4),
        )
        .width(Fill)
        .padding(4)
        .style(container::bordered_box)
        .into()
    }

    fn content(&self) -> Element<'_, Message> {
        container(text("Listen-Listen").size(24))
            .width(Fill)
            .height(Fill)
            .padding(4)
            .style(container::bordered_box)
            .into()
    }

    fn footer(&self) -> Element<'_, Message> {
        container(text("Listen-Listen").size(24))
            .width(Fill)
            .padding(4)
            .style(container::bordered_box)
            .into()
    }
}

pub fn update(_app_state: &mut AppState, message: Message) -> Task<Message> {
    match message {
        Message::Default => {
            println!("Do nothing");
            ().into()
        }
        Message::Minimize => {
            println!("minimize trigger");
            ().into()
        }
        Message::Maximize => {
            println!("maximize trigger");
            ().into()
        }
        Message::Exit => iced::exit(),
    }
}

pub fn theme(_app_state: &AppState) -> Theme {
    Theme::KanagawaDragon
}

fn main() -> iced::Result {
    let font_families = setup_fonts();
    iced::application(new_app_state, update, view)
        .theme(theme)
        .default_font(Font::with_name(font_families.default_font_family))
        .run()
}
