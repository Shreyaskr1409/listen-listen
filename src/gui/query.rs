use rusqlite::Connection;

use crate::data::music::Metadata;

pub fn init(db_path: &str) -> Result<Connection, rusqlite::Error> {
    Connection::open(db_path)
}

pub fn get_metadata(conn: Connection) -> Result<Vec<Metadata>, String> {
    let mut stmt = match conn.prepare(
        "SELECT path, title,
        track_no,
        disc_no,
        artist,
        album,
        album_artist,
        release_date FROM audio_files",
    ) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("Failed to prepare a SELECT statement: {e}");
            return Err(String::from("ERROR_POPULATING"));
        }
    };

    let audio_iter = match stmt.query_map([], |row| {
        Ok(Metadata {
            path: row.get(0)?,
            title: row.get(1)?,
            track_no: row.get(2)?,
            disc_no: row.get(3)?,
            artist: row.get(4)?,
            album: row.get(5)?,
            album_artist: row.get(6)?,
            _release_date: row.get(7)?,
        })
    }) {
        Ok(iter) => iter,
        Err(e) => {
            eprintln!("Failed to query audio files: {e}");
            return Err(String::from("ERROR_POPULATING"));
        }
    };

    let mut metadata_list: Vec<Metadata> = Vec::new();
    for song in audio_iter {
        match song {
            Ok(song) => metadata_list.push(song),
            Err(e) => {
                eprintln!("Failed to read audio file row: {e}");
                return Err(String::from("ERROR_POPULATING"));
            }
        }
    }

    Ok(metadata_list)
}

pub async fn scan_folders() -> Result<String, String> {
    println!("Scanning for files");
    Ok("Works".into())
}
