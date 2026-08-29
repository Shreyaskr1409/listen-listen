use rusqlite::Connection;

pub fn db_init(db_path: &str) -> Result<Connection, rusqlite::Error> {
    Connection::open(db_path)
}

pub async fn scan_for_files() -> Result<String, String> {
    println!("Scanning for files");
    Ok("Works".into())
}
