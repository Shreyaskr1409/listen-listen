mod component;
mod data;
mod query;
mod view;

use iced::{Element, Font, Task, Theme, widget::column};
use rusqlite::Connection;

use crate::{
    component::style::setup_fonts,
    query::{Metadata, get_metadata, init, scan_folders},
    view::{
        library::{LibraryMessage, LibraryView, player_library},
        player_footer::player_footer,
        player_header::player_header,
    },
};

#[derive(Debug, Default)]
pub struct AppState {
    library_view: LibraryView,
}

#[derive(Debug, Clone)]
pub enum Message {
    Library(LibraryMessage),
    Default,
    Minimize,
    Maximize,
    Exit,
}

pub fn new_app_state() -> AppState {
    AppState {
        library_view: LibraryView::default(),
    }
}

pub fn view(app_state: &AppState) -> Element<'_, Message> {
    column![app_state.header(), app_state.content(), app_state.footer()]
        .spacing(4)
        .padding(4)
        .into()
}

impl AppState {
    fn header(&self) -> Element<'_, Message> {
        player_header()
    }

    fn content(&self) -> Element<'_, Message> {
        player_library(&self)
    }

    fn footer(&self) -> Element<'_, Message> {
        player_footer()
    }
}

pub fn update(app_state: &mut AppState, message: Message) -> Task<Message> {
    match message {
        Message::Library(msg) => app_state.library_view.update(msg).map(Message::Library),

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

fn main() {
    let conn: Connection = match init("sonux.sqlite.db") {
        Err(e) => {
            eprintln!("Failed to initialize database: {e}");
            return;
        }
        Ok(c) => c,
    };

    let metadata_list: Vec<Metadata> = match get_metadata(conn) {
        Err(e) => {
            eprintln!("Error while fetching metadata: {e}");
            return;
        }
        Ok(m) => m,
    };

    let elem = metadata_list.get(48);

    if let Some(metadata) = elem {
        println!("Title: {}, Album: {}", metadata.title, metadata.album);
    } else {
        println!("No metadata found at index 1.");
    }

    let font_families = setup_fonts();
    if let Err(e) = iced::application(new_app_state, update, view)
        .theme(theme)
        .default_font(Font::with_name(font_families.default_font_family))
        .run()
    {
        eprintln!("Application exited due to error: {e}");
    }
}
