import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { KoordinaterModule } from './koordinater/koordinater.module';
import { MongooseModule } from '@nestjs/mongoose';

@Module({
  imports: [
    KoordinaterModule,
    MongooseModule.forRoot(
      'mongodb+srv://fest121:fest121@robot.bricdil.mongodb.net/',
    ),
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
