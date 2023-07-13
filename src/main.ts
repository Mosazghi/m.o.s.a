import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { NestExpressApplication } from '@nestjs/platform-express';
import * as session from 'express-session';
import * as passport from 'passport';
import { join } from 'path';
import { AppModule } from './app.module';
const PORT = 4000;

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalPipes(new ValidationPipe());

  app.useStaticAssets(join(__dirname, '..', 'public'));
  app.setBaseViewsDir(join(__dirname, '..', 'views'));
  app.setViewEngine('ejs');

  // Logger alle requests til konsollen
  app.use((req, res, next) => {
    console.log(`HTTP Method - ${req.method}, URL - ${req.url}`);
    next();
  });

  app.use(
    session({
      secret: 'PLSWORKFORME',
      resave: false,
      saveUninitialized: false,
    }),
  );
  app.use(passport.initialize());
  app.use(passport.session());

  await app.listen(PORT, '10.22.209.38', () => {
    console.log(`Lytter på http://10.22.209.38:${PORT}`);
  });
}
bootstrap();
