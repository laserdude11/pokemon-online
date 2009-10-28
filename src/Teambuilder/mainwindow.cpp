#include "mainwindow.h"
#include "../PokemonInfo/pokemoninfo.h"
#include "menu.h"
#include "teambuilder.h"

MainWindow::MainWindow() : m_menu(0), m_TB(0)
{
    resize (650, 680);
    setWindowTitle(tr("Pogeymon-Online"));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    PokemonInfo::init("db/");
    ItemInfo::init("db/");
    MoveInfo::init("db/");
    TypeInfo::init("db/");
    NatureInfo::init("db/");
    CategoryInfo::init("db/");
    AbilityInfo::init("db/");
    GenderInfo::init("db/");
    HiddenPowerInfo::init("db/");

    loadTeam(tr("Team/trainer.tp"));
    launchMenu();
}

TrainerTeam * MainWindow::trainerTeam()
{
    return & m_team;
}

void MainWindow::launchMenu()
{
    m_menu = new TB_Menu();

    /* We want to have space around the menu, so we put it in another widget ... */

    setCentralWidget(m_menu);
    setMenuBar(m_menu->createMenuBar(this));

    connect(m_menu, SIGNAL(goToTeambuilder()), SLOT(launchTeamBuilder()));
    connect(m_menu, SIGNAL(goToExit()), SLOT(close()));
    connect(m_menu, SIGNAL(goToOnline()), SLOT(goOnline()));
    connect(m_menu, SIGNAL(goToCredits()), SLOT(launchCredits()));
}

void MainWindow::launchCredits()
{
}

void MainWindow::launchTeamBuilder()
{
    m_TB = new TeamBuilder(trainerTeam());


    setCentralWidget(m_TB);
    setMenuBar(m_TB->createMenuBar(this));

    connect(m_TB, SIGNAL(done()), SLOT(launchMenu()));
}

void MainWindow::goOnline()
{
}

void MainWindow::loadTeam(const QString &path)
{
    trainerTeam()->loadFromFile(path);
}

void MainWindow::loadTeamDialog()
{
    loadTTeamDialog(*trainerTeam());
}