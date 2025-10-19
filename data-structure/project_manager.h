// #ifndef PROJECT_MANAGER_H
// #define PROJECT_MANAGER_H

// #include <QObject>
// #include <QSqlDatabase>
// // #include <Qimag>
// #include <QVariantList>

// class ProjectManager : public QObject {
//   Q_OBJECT
// public:
//   explicit ProjectManager(QObject *parent = nullptr);
//   ~ProjectManager();

//   // Create a new project file (returns true on success)
//   bool createProject(const QString &filePath,
//                      const QString &projName,
//                      const QString &author,
//                      const QString &comment);

//   // Open existing project file
//   bool openProject(const QString &filePath);

//   // Close project
//   void closeProject();

// private:

//   bool initSchema();
//   QByteArray imageToBlob(const QImage &img, const char *format = "PNG") const;
//   QImage blobToImage(const QByteArray &blob) const;
//   QByteArray makeThumbnail(const QImage &img, int maxDim = 256) const;
//   QString nowUtcIso() const;

// private:
//   QSqlDatabase m_db;
//   QString m_connName;
// };

// #endif // PROJECT_MANAGER_H
