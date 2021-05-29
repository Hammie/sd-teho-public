// Антонио Бетанкур - потомок Франциско Бетанкура
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуй-здравствуй... Чего хотел, парень?";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". И я просто хотел познакомиться. понимаешь, я здесь недавно, хожу по городу, беседую с людьми. Налаживаю контакты - вот как это можно назвать.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Чего тебе на этот раз?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Антонио, мне сказали, что ты хорошо знаком с историей Острова. У меня в связи с этим есть к тебе один вопрос.";
					link.l4.go = "dolly";
				}
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у тебя дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Прекрасно. Очень правильно делаешь, поскольку мы здесь все - одна большая семья. Ну, не считая, конечно, нарвалов и гнусных ривадос. Меня зовут Антонио, Антонио Бетанкур. Внук Франциско Бетанкура, если это тебе о чем-то говорит.";
			link.l1 = "Франциско Бетанкур? Где-то я уже слышал это имя... А, точно! Его мне назвал Диос, и также оно встречается в хрониках Альворадо...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Кто такой Диос - мне неведомо, а что до капитана Альворадо - гостил такой у нас на Острове. Я лично видел его, когда был мальчишкой. Он уплыл с Острова и писал потом про него в своих сочинениях. А Франциско Бетанкур - испанский гранд, адмирал, командующий военной эскадрой\nИменно с него берет начало история нашего Острова, поскольку все ривадос - это потомки рабов, которые были в трюмах 'Тартаруса', флагмана эскадры, а нарвалы - соответственно дети детей первых белых поселенцев, людей команд 'Тартаруса', 'Сан-Августина' и 'Сан-Херонимо'.";
			link.l1 = "Ого! Так ты, получается, родился тут?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Именно. Я прямой потомок человека, фактически заселившего Остров.";
			link.l1 = "Ясно. Рад встрече и знакомству, Антонио! Еще увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Хм... Спрашивай, дружище, конечно. Если знаю - конечно, отвечу.";
			link.l1 = "Скажи, ты помнишь то время, когда галеон 'Сан-Херонимо' еще стоял на поверхности?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Конечно, помню. Это был очень примечательный корабль. На нем находилась интересная индейская статуя, у которой эти мерзкие язычники ривадос проводили жертвоприношения.";
			link.l1 = "И как они их проводили? Вырезали ножом сердца, как майя, или рубили головы?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "Нет, что ты... Это была особенная статуя - она сама затягивала в себя жертв и они бесследно исчезали. Дьявольское порождение... Слава Господу, она утонула вместе с кораблем и уже никому не принесет вреда. И что примечательно - жертвоприношения всегда проводились в одно и то же время, утром. Тусклая статуя внезапно начинала сверкать золотом в лучах восходящего солнца, и над ней появлялось сияние\nВот тогда-то они и приводили к ней своих жертв, в основном это были пленники из клана нарвалов. Поставят рядом с ней человека - оп! И нет его, как корова языком слизала, прости за нелепое сравнение.";
			link.l1 = "Очень занятно! А природу этой статуи никто не пытался понять?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Что ты! Во-первых, ривадос никого постороннего даже близко не подпускали к 'Сан-Херонимо', а во-вторых, добропорядочному католику следует держаться как можно дальше от дьявольских порождений.";
			link.l1 = "Понятно. Смотрю, ты как-то недолюбливаешь ривадос. Или мне кажется?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Недолюбливаю? Да я их терпеть не могу, грязных нехристей! Если хочешь знать, то мой дед был капитаном корабля, на котором эти черномазые во главе с проклятым богоотступником Ривадосом подняли бунт. Правильно сделал мой дед, что подвесил этого мерзкого бунтовщика в трюме. А еще, у меня от деда оставалась реликвия - великолепный ключ от казны 'Санта-Анны'\nГде сейчас эта казна - никто не ведает, может, на дне среди крабов, но ключ этот был для меня как память - и тот украли! Я уверен, что это сделали черномазые. Наверняка думают найти казну. Ну, раз за столько лет никто не нашел, то и они не отыщут, ха-ха! Негодяи...";
			link.l1 = "Ясно. Спасибо за интересную историю!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Да не за что, всегда рад поболтать!";
			link.l1 = "До свидания!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Слушаю тебя, парень.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Так ты, выходит, кроме Острова ничего на свете и не видел?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ты здесь родился... А почему не входишь в клан нарвалов? Я думал, все коренные белые - нарвалы...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "А чем ты занимаешься на Острове?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Скажи, а тебе никогда не хотелось покинуть Остров хотя бы ненадолго? Посмотреть мир...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извини...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Выходит, так. Но не считай из-за этого меня глупцом или ограниченным. Мне досталась от деда отличная библиотека, и отец дал мне достойное образование. Я знаю древнюю историю, современную историю, географию, астрономию, умею разговаривать на английском, французском и испанском языках, а также на латыни\nМногие моряки, объездившие свет, не знают столько, сколько знаю я. Книги - отличный источник знаний, скажу я тебе, приятель. Так что хоть я и не видел ничего, кроме этих корабельных остовов, мысленно я побывал и в Европе, и в Китае, и в Индии...";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Это не так, хотя на девяносто процентов ты прав. Но я не нарвал, и не желаю им становиться. Зачем? Чтобы стоять на часах, как дураку, и рубиться с ривадос? Нет уж, увольте. Я - человек совсем другого воспитания. Я предпочитаю жить независимо и посвящать все свободное время чтению.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "От отца мне досталось неплохое наследство, и я очень экономно его расходую. Так что мне нет нужды шариться по корабельным остовам, для того чтобы раздобыть пару побрякушек на пропитание. В сказочные богатства на погибших кораблях я не верю\nЕдинственное сокровище, о котором мне достоверно известно, что оно существует - казна 'Санта-Анны', одного из кораблей эскадры моего деда. Это тяжелый кованый сундук. Но никому за все годы существования Острова так и не удалось найти его\nДа, я тут думаю написать подробную историю Острова, с момента его появления, основанную на рассказах очевидцев. Как думаешь, стоит этим заняться?";
			link.l1 = "Уверен, что стоит. Я знаю на Архипелаге как минимум одного человека, который наверняка заплатил за такой труд немало золота. Так что - дерзай...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Такие мысли регулярно посещают меня. Возможно, если бы тут появился надежный корабль, способный пройти через течение и устоять в штормах, я бы рискнул. Мне жутко хочется взглянуть на то, что так занимательно описано в моих книгах! Но пока это только мечты...";
			link.l1 = "Мечты имеют свойство сбываться. Главное - верить в них...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдет!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдет!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}